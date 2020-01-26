CC=g++
OBJS= MtmParkingLot.o Time.o ParkingLot.o ParkingLotPrinter.o ParkingSpot.o
EXEC=MtmParkingLot
SRVR_FLAGS =
DEBUG_FLAG=
COMP_FLAG= -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG

$(EXEC) :$(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@ $(SRVR_FLAGS)
	
MtmParkingLot.o: MtmParkingLot.cpp ParkingLotTypes.h Time.h ParkingLotPrinter.h ParkingLot.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

Time.o: Time.cpp Time.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
	
ParkingLot.o: ParkingLot.cpp ParkingLot.h UniqueArray.h UniqueArrayImp.h ParkingLotTypes.h Time.h ParkingLotPrinter.h	
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
	
ParkingLotPrinter.o: ParkingLotPrinter.cpp ParkingLotPrinter.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

ParkingSpot.o: ParkingSpot.cpp ParkingSpot.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp

clean:
	rm -f $(OBJS) $(EXEC)

