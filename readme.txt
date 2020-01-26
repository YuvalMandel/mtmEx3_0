***you must use the provided MtmParkingLot.cpp, otherwise you will enter an infinite loop***
***if you use different input/valid output files then you need to be sure they are correct. incorrect input files will result in an infinite loop***
***if you don't compile your code on the server and make "mtm_ex3.exe" elsewhere it might not work***

this script will check your output and compare it with the valid output, as well as check for any memory errors using valgrind.
if you get different outputs you will be notified and asked for action.
if a memory error occurs then you will be notified and the script will stop.
no files will be created unless you get different output or a memory error occurs.

Requirements:

1) io_files folder containing input.txt and output_valid.txt files with valid input/output (a folder containing 100 of each provided provided in zip, but you can use your own IF they are 100% valid)
2) custom MtmParkingLot.cpp (provided in zip)
3) server_test file (provided in zip)
4) your code files, including all .h and .cpp files required for ParkingLot, which you will compile on the server

Instructions:

1) extract files
2) place files on the servers where you plan on compiling your code (place the io_folder folder itself, without taking any files out of it)
2*) if the folder containing your code files already had MtmParkingLot.cpp then replace it with the one provided in the zip
3) in the console, get to the folder in which the script and your code files are
4) type "chmod 700 server_test" without the parentheses
5) compile your code as you normally would, but make sure your executable is named "mtm_ex3.exe" (g++ -std=c++11 -Wall -Werror -pedantic-errors -g -o mtm_ex3.exe *.cpp)
6) run the script by typing the command "./server_test" in the console. if you did everything right then it should start
