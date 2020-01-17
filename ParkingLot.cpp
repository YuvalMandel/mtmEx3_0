#include "ParkingLot.h"
#include "UniqueArray.h"
#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingLotPrinter.h"

using namespace ParkingLotUtils;
using namespace MtmParkingLot;



ParkingLot::ParkingLot(unsigned int *parkingBlockSizes)
: parking_lot(parkingBlockSizes[0] + parkingBlockSizes[1] +
              parkingBlockSizes[2])
{

    int motorbike_end = parkingBlockSizes[0];
    int handycapped_end = parkingBlockSizes[0] + parkingBlockSizes[1];
    int car_end = parkingBlockSizes[0] + parkingBlockSizes[1] +
            parkingBlockSizes[2];

    lot_size=car_end;


    for (int i = 0; i < motorbike_end; ++i) {

        //ParkingLotUtils::Time arrival(0,0,0);
        ParkingLocation current_parking_location =
                ParkingLocation(MOTORBIKE, i);

        parking_lot.insert(current_parking_location);

    }

    for (int i = motorbike_end; i < handycapped_end; ++i) {

        ParkingLocation current_parking_location =
                ParkingLocation(HANDICAPPED, i);

        parking_lot.insert(current_parking_location);

    }

    for (int i = handycapped_end; i < car_end; ++i) {

        ParkingLocation current_parking_location =
                ParkingLocation(CAR, i);

        parking_lot.insert(current_parking_location);

    }

}
typedef UniqueArray< ParkingLocation,
        ParkingLocationCompare> UniqueParkingArray;

//filters
//---------------------------------------------------

//filter motorcycle type
//class TypeFilterMotorcycle: public UniqueParkingArray ::Filter{
//public:
//    bool operator()(const ParkingLocation &location )
//    {
//        if (location.getParkingBlock()==MOTORBIKE)
//            return true;
//    }
//
//};
//
////filter motorcycle type
//class TypeFilterhandicap: public UniqueParkingArray ::Filter{
//public:
//    bool operator()(const ParkingLocation &location )
//    {
//        if (location.getParkingBlock()==HANDICAPPED)
//            return true;
//    }
//
//};

//filter car type
class TypeFilterCar: public UniqueParkingArray ::Filter{

    VehicleType filter_type;

public:
    explicit TypeFilterCar(VehicleType type_to_filter){
        filter_type=type_to_filter;
    }

    bool operator()(const ParkingLocation &location ) const override
    {

        return (location.getParkingBlock() == filter_type)&& location.check_occupation();

    }

};

ParkingLocation* find_open_spot(UniqueParkingArray
filtered_array, int lot_size, int& index) {
    for (int i = 0; i < lot_size; ++i) {

        ParkingLocation *free_location = filtered_array
                .getElementByIndex(i);

        if (free_location != NULL) {

            index=i;

            return free_location;


        }

    }
    return NULL;
}


ParkingLotUtils::ParkingResult ParkingLot::enterParking(
        ParkingLotUtils::VehicleType vehicleType,
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::Time entranceTime) {


    UniqueParkingArray filtered_array(parking_lot.filter(TypeFilterCar
                                                                 (vehicleType)));

    for (int i = 0; i < lot_size; ++i) {

        ParkingLocation *temp_location = parking_lot.getElementByIndex(i);

        if (temp_location->get_license_plate() == licensePlate) {

            ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                                                              *temp_location);//slicing
            return VEHICLE_ALREADY_PARKED;
        }
    }

    int index = 0;

    ParkingLocation *free_location = find_open_spot
            (filtered_array, lot_size, index);

    if ((free_location == NULL) && (vehicleType == HANDICAPPED)) {

        UniqueParkingArray filtered_handicapped(
                parking_lot.filter(TypeFilterCar(CAR)));

        free_location = find_open_spot(
                filtered_handicapped, lot_size, index);
    }

    if (free_location == NULL) {

        ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
        return NO_EMPTY_SPOT;

    } else {

        parking_lot.remove(*free_location);


        parking_lot.insert(ParkingLocation(vehicleType, index,
                                           true, entranceTime, licensePlate,
                                           0));

        ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                                        licensePlate, entranceTime);
        ParkingLotPrinter::printEntrySuccess(std::cout, *free_location);

        return SUCCESS;

    }

}

int calculate_price(ParkingLocation parking_session,Time exit_time)
{
    int price=0;
    Time total_parking_time(exit_time-parking_session.get_entrance_time());


    if (parking_session.get_vehicle_type()==MOTORBIKE)
    {
        price=10+(total_parking_time.toHours()-1)*5;

        if(price>35)
        {
            price=35;
        }
    }
    if (parking_session.get_vehicle_type()==CAR)
    {
        price=20+(total_parking_time.toHours()-1)*10;

        if(price>70)
        {
            price=70;
        }
    }

    if (parking_session.get_vehicle_type()==HANDICAPPED)
    {

        price=15;

    }
    if (parking_session.got_fine())
    {
        price=price+250;
    }
    return price;

}

ParkingResult ParkingLot::exitParking(
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::Time exitTime) {

    for (int i = 0; i < lot_size; ++i) {

        ParkingLocation *temp_location = parking_lot.getElementByIndex(i);

        if (temp_location->get_license_plate() == licensePlate) {

            VehicleType temporary_type=temp_location->getParkingBlock();

            ParkingLotPrinter::printVehicle(std::cout,
                    temp_location->get_vehicle_type(),licensePlate,
                    temp_location->get_entrance_time());
            int price=0;

            price=calculate_price(*temp_location,exitTime);

            ParkingLotPrinter::printExitSuccess(std::cout,*temp_location,
                    exitTime,price);

            parking_lot.remove(*temp_location);

            parking_lot.insert(ParkingLocation(temporary_type,i,
                    false));

            return SUCCESS;
        }
    }
    ParkingLotPrinter::printExitFailure(std::cout,licensePlate);
    return VEHICLE_NOT_FOUND;




    //return VEHICLE_ALREADY_PARKED;
}

ParkingLotUtils::ParkingResult ParkingLot::getParkingSpot(
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::ParkingSpot &parkingSpot) const {

    for(int i=0; i<lot_size;i++)
    {
        ParkingLocation *temp_location=parking_lot.getElementByIndex(i);
        if(licensePlate==temp_location->get_license_plate())
        {
            parkingSpot=*temp_location;

            return(SUCCESS);

        }

    }

    return VEHICLE_NOT_FOUND;
}

void ParkingLot::inspectParkingLot(
        ParkingLotUtils::Time inspectionTime) {

    for (int i = 0; i <lot_size; ++i) {


        ParkingLocation *temp_location=parking_lot.getElementByIndex(i);

        Time total_parking_time=inspectionTime-
                temp_location->get_entrance_time();

        if(total_parking_time.toHours()>24)

            temp_location->give_fine();

    }




}

ostream &MtmParkingLot::operator<<(ostream &os, const ParkingLot &parkingLot) {

        ParkingLotPrinter::printParkingLotTitle(os);
    for (int i = 0; i < parkingLot.lot_size; ++i) {

        ParkingLocation *temp_location=parkingLot.parking_lot
                .getElementByIndex(i);

        if(temp_location->check_occupation()) {

            ParkingLotPrinter::printVehicle(os,
                    temp_location->get_vehicle_type(),
                    temp_location->get_license_plate(), temp_location->get_entrance_time());
            ParkingLotPrinter::printParkingSpot(os,*temp_location);
        }

    }

    return os;
}

//ostream& operator<<(ostream &os, const ParkingLot &parkingLot) {
//
//    ParkingLotPrinter::printParkingLotTitle(os);
//    for (int i = 0; i < parkingLot.lot_size; ++i) {
//
//        ParkingLocation *temp_location=parkingLot.parking_lot
//                .getElementByIndex(i);
//
//        if(temp_location->check_occupation()) {
//
//            ParkingLotPrinter::printVehicle(os,
//                    temp_location->get_vehicle_type(),
//                    temp_location->get_license_plate(), temp_location->get_entrance_time());
//            ParkingLotPrinter::printParkingSpot(os,*temp_location);
//        }
//
//    }
//
//    return os;
//}

ParkingLocation::ParkingLocation(
        ParkingLotUtils::VehicleType parkingBlock, unsigned int parkingNumber,
        bool occupied, ParkingLotUtils::Time arrival_time, LicensePlate license_plate,
        bool received_fine, VehicleType type_of_vehicle):
        ParkingSpot(parkingBlock, parkingNumber),
        occupied(occupied),
        arrival_time(arrival_time),
        license_plate(license_plate),
        received_fine(received_fine),
        type_of_vehicle(type_of_vehicle)

{

}

bool ParkingLocation::check_occupation() const {
    return this->occupied;
}

ParkingLotUtils::LicensePlate
ParkingLocation::get_license_plate() const {
    return ParkingLotUtils::LicensePlate();
}

ParkingLotUtils::VehicleType
ParkingLocation::get_vehicle_type() const {
    return type_of_vehicle;
}

ParkingLotUtils::Time
ParkingLocation::get_entrance_time() const {
    return arrival_time;
}

bool ParkingLocation::got_fine() const {
    return received_fine;
}

void ParkingLocation::give_fine() {

    this->received_fine=true;

}


