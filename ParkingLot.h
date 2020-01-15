#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"





namespace MtmParkingLot {


    using namespace ParkingLotUtils;
    using std::ostream;

    class ParkingLocation: public ParkingSpot{

    private:

        bool occupied;
        Time arrival_time;
        LicensePlate license_plate;
        int num_of_fines;

    public:

        explicit ParkingLocation(VehicleType parkingBlock = FIRST,
                unsigned int parkingNumber = 0,
                bool occupied = false,
                Time arrival_time=(0,0,0),
                LicensePlate license_plate = " ",
                int num_of_fines = 0);

    };

    class ParkingLocationCompare{

    public:
        ParkingLocationCompare() = default;
        bool operator()(const ParkingLocation& location_0,
                        const ParkingLocation& location_1) const {

            return (!(location_0 < location_1)) && (!(location_1 < location_0));

        }

    };

    class ParkingLot {
    private:

        UniqueArray<ParkingLocation, ParkingLocationCompare> parking_lot;
        int lot_size;


    public:

        ParkingLot(unsigned int parkingBlockSizes[]);
//        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
