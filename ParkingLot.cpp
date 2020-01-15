#include "ParkingLot.h"
#include "UniqueArray.h"
#include "ParkingLotTypes.h"


MtmParkingLot::ParkingLot::ParkingLot(unsigned int *parkingBlockSizes)
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
typedef UniqueArray< MtmParkingLot::ParkingLocation,
        MtmParkingLot::ParkingLocationCompare> UniqueParkingArray;

//filters
//---------------------------------------------------

//filter motorcycle type
class TypeFilterMotorcycle: public UniqueParkingArray ::Filter{
public:
    bool operator()(const MtmParkingLot::ParkingLocation &location )
    {
        if (location.getParkingBlock()==MtmParkingLot::MOTORBIKE)
            return true;
    }

};

//filter motorcycle type
class TypeFilterhandicap: public UniqueParkingArray ::Filter{
public:
    bool operator()(const MtmParkingLot::ParkingLocation &location )
    {
        if (location.getParkingBlock()==MtmParkingLot::HANDICAPPED)
            return true;
    }

};

//filter car type
class TypeFilterCar: public UniqueParkingArray ::Filter{
public:
    bool operator()(const MtmParkingLot::ParkingLocation &location ) const override
    {
        if (location.getParkingBlock()==MtmParkingLot::CAR)
            return true;

        return false;
    }

};


ParkingLotUtils::ParkingResult MtmParkingLot::ParkingLot::enterParking(
        ParkingLotUtils::VehicleType vehicleType,
        ParkingLotUtils::LicensePlate licensePlate,
        ParkingLotUtils::Time entranceTime) {

//    UniqueParkingArray filtered_array(lot_size);
//
    if( vehicleType == MtmParkingLot::CAR)
    {
        UniqueParkingArray filtered_array(parking_lot.filter(TypeFilterCar()));
    }


    return VEHICLE_ALREADY_PARKED;
}

MtmParkingLot::ParkingLocation::ParkingLocation(
        ParkingLotUtils::VehicleType parkingBlock, unsigned int parkingNumber,
        bool occupied, ParkingLotUtils::Time arrival_time, LicensePlate license_plate,
        int num_of_fines):
        ParkingSpot(parkingBlock, parkingNumber),
        occupied(occupied),
        arrival_time(arrival_time),
        license_plate(license_plate),
        num_of_fines(num_of_fines)

{

}


