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
        bool received_fine;
        VehicleType type_of_vehicle;

    public:

        explicit ParkingLocation(VehicleType parkingBlock = FIRST,
                unsigned int parkingNumber = 0,
                bool occupied = false,
                Time arrival_time=Time(0,0,0),
                LicensePlate license_plate = " ",
                bool received_fine = 0, VehicleType type_of_vehicle=CAR) ;

        bool check_occupation() const;

        LicensePlate get_license_plate() const;

        VehicleType get_vehicle_type() const;

        Time get_entrance_time() const;

        bool got_fine() const;



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

        explicit ParkingLot(unsigned int parkingBlockSizes[]);
//        ~ParkingLot();
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);
        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

    };
    ostream& operator<<(ostream& os, const ParkingLot& parkingLot);
}

#endif //MTMPARKINGLOT_PARKINGLOT_H
