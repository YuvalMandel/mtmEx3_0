#include "ParkingLot.h"
#include "UniqueArray.h"


MtmParkingLot::ParkingLot::ParkingLot(unsigned int *parkingBlockSizes)
: parking_lot(parkingBlockSizes[0] + parkingBlockSizes[1] +
              parkingBlockSizes[2])
{

    int motorbike_end = parkingBlockSizes[0];
    int handycapped_end = parkingBlockSizes[0] + parkingBlockSizes[1];
    int car_end = parkingBlockSizes[0] + parkingBlockSizes[1] +
            parkingBlockSizes[2];


    for (int i = 0; i < motorbike_end; ++i) {

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

MtmParkingLot::ParkingLocation::ParkingLocation(
        ParkingLotUtils::VehicleType parkingBlock, unsigned int parkingNumber,
        bool occupied, ParkingLotUtils::Time arrival_time, LicensePlate license_plate,
        int num_of_fines):
        ParkingSpot(parkingBlock, parkingNumber),
        occupied(occupied),
        arrival_time(arrival_time),
        license_plate(license_plate),
        num_of_fines(num_of_fines){



}

MtmParkingLot::ParkingLocation::compare(ParkingLocation



}
