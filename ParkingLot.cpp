#include "ParkingLot.h"
#include "UniqueArray.h"
#include "ParkingLotTypes.h"
#include "ParkingLotPrinter.h"

using namespace ParkingLotUtils;
using namespace MtmParkingLot;

#define NUM_PARK_TYPES 3
#define VEHICLE_TYPES {MOTORBIKE, HANDICAPPED, CAR};

unsigned int ParkingLot::getShift(VehicleType vehicle_type){

    if(vehicle_type == MOTORBIKE)
        {return 0;}
    else if(vehicle_type == HANDICAPPED)
        {return motorbike_size;}
    else if(vehicle_type == CAR)
        {return motorbike_size + handicapped_size;}

    return 0;

}

ParkingLot::ParkingLot(unsigned int *parkingBlockSizes)
: parking_lot(parkingBlockSizes[0] + parkingBlockSizes[1] +
              parkingBlockSizes[2])
{
    motorbike_size = parkingBlockSizes[0];
    handicapped_size = parkingBlockSizes[1];
    car_size = parkingBlockSizes[2];

    unsigned int type_lengths[NUM_PARK_TYPES] =
            {motorbike_size, handicapped_size, car_size};

    lot_size = int(motorbike_size + handicapped_size + car_size);

    VehicleType vehicle_types[3] = VEHICLE_TYPES;

    for (int j = 0; j < NUM_PARK_TYPES; ++j) {

        for (unsigned int i = 0; i < type_lengths[j]; ++i) {

            ParkingLocation current_parking_location =
                    ParkingLocation(vehicle_types[j], i);
                            //getShift(vehicle_types[j]) + i); //TODO choose

            parking_lot.insert(current_parking_location);

        }

    }

}
typedef UniqueArray< ParkingLocation,
        ParkingLocationCompare> UniqueParkingArray;

//filter car type
class TypeFilterVehicleType: public UniqueParkingArray ::Filter{

    VehicleType filter_type;

public:
    explicit TypeFilterVehicleType(VehicleType type_to_filter){
        filter_type = type_to_filter;
    }

    bool operator()(const ParkingLocation &location ) const override
    {
        return (location.getParkingBlock() == filter_type)&& !location
                .checkOccupation();
    }

};

ParkingLocation* find_open_spot(const UniqueParkingArray&
filtered_array, int lot_size, int& index) {
    for (int i = 0; i < lot_size; ++i) {

        ParkingLocation *free_location = filtered_array.getElementByIndex(i);

        if (free_location != nullptr) {

            index=i;

            return free_location;


        }

    }
    return nullptr;
}

ParkingLotUtils::ParkingResult ParkingLot::enterParking(
        ParkingLotUtils::VehicleType vehicleType,
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::Time entranceTime) {

    UniqueParkingArray filtered_array(
            parking_lot.filter(TypeFilterVehicleType(vehicleType)));

    for (int i = 0; i < lot_size; ++i) {

        ParkingLocation *temp_location = parking_lot.getElementByIndex(i);

        if (temp_location->getLicensePlate() == licensePlate) {

            ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                    licensePlate, temp_location->getEntranceTime());

            ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                                                              *temp_location);
            return VEHICLE_ALREADY_PARKED;
        }
    }

    int index = 0;

    ParkingLocation *free_location = find_open_spot
            (filtered_array, lot_size, index);

    UniqueParkingArray filtered_handicapped(
            parking_lot.filter(TypeFilterVehicleType(CAR)));

    if ((free_location == nullptr) && (vehicleType == HANDICAPPED)) {

        free_location = find_open_spot(filtered_handicapped, lot_size,
                index);
    }

    if (free_location == nullptr) {

        ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                                        licensePlate, entranceTime);
        ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
        return NO_EMPTY_SPOT;

    } else {

        parking_lot.remove(*free_location);

        parking_lot.insert(ParkingLocation(free_location->getParkingBlock(), index -
                                                   getShift(free_location->getParkingBlock()),
                                           true, entranceTime, licensePlate,
                                           false,vehicleType));

        ParkingLotPrinter::printVehicle(std::cout, vehicleType,
                                        licensePlate, entranceTime);

        ParkingLotPrinter::printEntrySuccess(std::cout, *free_location);

        return SUCCESS;

    }

}

unsigned int calculate_price(ParkingLocation parking_session,Time exit_time)
{
    unsigned int price = 0;

    Time total_parking_time(exit_time- parking_session.getEntranceTime());

    if(total_parking_time.toHours() == 0) return 0; // TODO: remove row later

    if (parking_session.getVehicleType() == MOTORBIKE){

        price = 10 + (total_parking_time.toHours() - 1)*5;

        if (price > 35){

            price = 35;

        }

    }

    if (parking_session.getVehicleType() == CAR){

        price = 20 + (total_parking_time.toHours() - 1)*10;

        if (price > 70){

            price = 70;

        }

    }

    if (parking_session.getVehicleType() == HANDICAPPED) {

        price = 15;

    }

    if (parking_session.gotFine()){

        price = price + 250;

    }

    return price;
}

ParkingResult ParkingLot::exitParking(
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::Time exitTime) {

    for (int i = 0; i < lot_size; ++i) {

        ParkingLocation *temp_location = parking_lot.getElementByIndex(i);
        LicensePlate temp_plate= temp_location->getLicensePlate();

        if (temp_location->getLicensePlate() == licensePlate) {

            VehicleType temporary_type = temp_location -> getParkingBlock();

            ParkingLotPrinter::printVehicle(std::cout,
                                            temp_location->getVehicleType(), licensePlate,
                                            temp_location->getEntranceTime());

            unsigned int price = 0;

            price = calculate_price(*temp_location, exitTime);

            ParkingLotPrinter::printExitSuccess(std::cout, *temp_location,
                    exitTime, price);

            parking_lot.remove(*temp_location);

            parking_lot.insert(ParkingLocation(temporary_type,
                                               i - getShift(temporary_type), false));

            return SUCCESS;
        }
    }

    ParkingLotPrinter::printExitFailure(std::cout,licensePlate);

    return VEHICLE_NOT_FOUND;

}

ParkingLotUtils::ParkingResult ParkingLot::getParkingSpot(
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::ParkingSpot &parkingSpot) const {

    for(int i = 0; i < lot_size; i++)
    {
        ParkingLocation *temp_location = parking_lot.getElementByIndex(i);
        if(licensePlate == temp_location->getLicensePlate())
        {
            parkingSpot=*temp_location;

            return(SUCCESS);
        }
    }

    return VEHICLE_NOT_FOUND;
}

void ParkingLot::inspectParkingLot(
        ParkingLotUtils::Time inspectionTime) {

    int fined = 0;

    for (int i = 0; i < lot_size; ++i) {

        ParkingLocation *temp_location = parking_lot.getElementByIndex(i);

        Time total_parking_time = inspectionTime -
                temp_location->getEntranceTime();

        if(total_parking_time.toHours() > 24 &&
                temp_location->checkOccupation() && !(temp_location->gotFine())){

            temp_location->giveFine();

            fined++;

        }

    }

    ParkingLotPrinter::printInspectionResult(std::cout, inspectionTime, fined);

}

ostream &MtmParkingLot::operator<<(ostream &os, const ParkingLot &parkingLot) {

        ParkingLotPrinter::printParkingLotTitle(os);
    for (int i = 0; i < parkingLot.lot_size; ++i) {

        ParkingLocation *temp_location = parkingLot.parking_lot
                .getElementByIndex(i);

        if(temp_location->checkOccupation()) {

            ParkingLotPrinter::printVehicle(os,
                                            temp_location->getVehicleType(),
                                            temp_location->getLicensePlate(),
                                            temp_location->getEntranceTime());

            ParkingLotPrinter::printParkingSpot(os,*temp_location);

        }
    }

    return os;
}

ParkingLocation::ParkingLocation(
        ParkingLotUtils::VehicleType parkingBlock, unsigned int parkingNumber,
        bool occupied, ParkingLotUtils::Time arrival_time, LicensePlate license_plate,
        bool received_fine, VehicleType type_of_vehicle):
        ParkingSpot(parkingBlock, parkingNumber),
        occupied(occupied),
        arrival_time(arrival_time),
        license_plate(license_plate),
        received_fine(received_fine),
        type_of_vehicle(type_of_vehicle){

}

bool ParkingLocation::checkOccupation() const {
    return this -> occupied;
}

ParkingLotUtils::LicensePlate
ParkingLocation::getLicensePlate() const {
    return this -> license_plate;
}

ParkingLotUtils::VehicleType
ParkingLocation::getVehicleType() const {
    return type_of_vehicle;
}

ParkingLotUtils::Time
ParkingLocation::getEntranceTime() const {
    return arrival_time;
}

bool ParkingLocation::gotFine() const {
    return received_fine;
}

void ParkingLocation::giveFine() {
    this -> received_fine = true;
}




