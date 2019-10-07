*******************************************************
*  Name      :  Tobby Lie       
*  Student ID:  103385744              
*  Class     :  CSCI 2312           
*  HW#       :  Final Project               
*  Due Date  :  Nov. 21, 2017
*******************************************************


                 Read Me


*******************************************************
*  Description of the program
*******************************************************

The program “Battleships" will utilize object oriented concepts
in order to implement a Battleship game for a user vs. computer.

Extra credit completed in this program.

*******************************************************
*  Source files
*******************************************************

Name:  main.cpp
   Main program.  This is the driver program that calls sub-functions

Name:  Grid.h
   Contains the prototypes for the Battleship program game board functions.

Name: Grid.cpp
   Implementation for BattleShip program game board functions.

Name:  Player.h
   Contains the prototypes for the Battleship program player functions.
   Will control gameplay.

Name: Player.cpp
   Implementation for BattleShip program player functions.

Name:  WaterVehicle.h
   Contains the prototypes for the Battleship program game ships functions.

Name: WaterVehicle.cpp
   Implementation for BattleShip program game ships functions.

   
*******************************************************
*  Circumstances of programs
*******************************************************

   The program runs successfully.  
   
   The program was developed and tested on Xcode. It was 
   compiled, run, and tested on gcc 4.8 on csegrid.ucdenver.pvt.


*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip LieFinalProject.zip

   Now you should see a directory named LieFinalProject with the files:
        main.cpp
	Grid.h
	Grid.cpp
	Player.h
	Player.cpp
	WaterVehicle.h
	WaterVehicle.cpp
	ship_placement.csv
	CSCI 2312 Object Oriented Final Project Design.pdf
        makefile
        Readme.txt

2. Build the program.

    Change to the directory that contains the file by:
    % cd LieFinalProject 

    Compile the program by:
    % make

3. Run the program by:
   % ./finalproject

4. Delete the obj files, executables, and core dump by
   %./make clean
