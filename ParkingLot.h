#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"
#include "ParkingLotPrinter.h"

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

        bool checkOccupation() const;
        LicensePlate getLicensePlate() const;
        VehicleType getVehicleType() const;
        Time getEntranceTime() const;
        bool gotFine() const;
        void giveFine();

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
        unsigned int motorbike_size;
        unsigned int handicapped_size;
        unsigned int car_size;

        unsigned int getShift(VehicleType vehicle_type);

    public:

        explicit ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot() = default;
        ParkingResult enterParking(VehicleType vehicleType, LicensePlate licensePlate, Time entranceTime);
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);
        ParkingResult getParkingSpot(LicensePlate licensePlate, ParkingSpot& parkingSpot) const;
        void inspectParkingLot(Time inspectionTime);

        friend ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

    };

    ostream& operator<<(ostream& os, const ParkingLot& parkingLot);

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
