//Tobby Lie 103385744
//CSCI 2312
//Final Project
//November 3, 2017
//WaterVehicle class prototypes

#ifndef WaterVehicle_h
#define WaterVehicle_h

#include <string>
#include <iostream>

using namespace std;

// exception classes
class invalidX_Coor{
public:
    void errorMessage(){
        cout << "Error: Invalid x coordinate input!" << endl;
        cout << "Program terminating." << endl;
        exit(0);
    }
};
class invalidY_Coor{
public:
    void errorMessage(){
        cout << "Error: Invalid y coordinate input!" << endl;
        cout << "Program terminating." << endl;
        exit(0);
    }
};
class invalidOrientation{
public:
    void errorMessage(){
        cout << "Error: Invalid orientation input!" << endl;
        cout << "Program terminating." << endl;
        exit(0);
    }
};
class blankField{
public:
    void errorMessage(){
        cout << "Error: There is a blank field!" << endl;
        cout << "Program terminating." << endl;
        exit(0);
    }
};

class WaterVehicle{
private:
    string typeOfShip;
    int length;
    int startLocation_x; // will convert this to int later for actual coordinates
    int startLocation_y;// head of ship starts here
    bool sunk;
    bool hit;
    bool isHorizontal; // if horizontal ship will extend out from head to the right by however
    // much length is, if vertical, ship will extend from head down
    int hitCounter = 0; // starts at 0 hits
public:
    WaterVehicle(); // default constructor
    WaterVehicle(int _x, int _y, bool _sunk, bool _hit, bool _isHorizontal);
    string getTypeOfShip() const;
    void setHitCounter(int count);
    int getHitCounter() const;
    void setTypeOfShip(string _typeOfShip);
    int getLength() const;
    void setLength(int _length);
    int getLocation_x() const;
    void setLocation_x(string _x) throw(invalidX_Coor,blankField); // will take in char input and perform conversion to int for this parameter
    int getLocation_y() const;
    void setLocation_y(string _y) throw(invalidY_Coor,blankField);
    virtual bool isSunk() const; // VIRTUAL
    void setSunkStatus(bool sunkStatus); // can set bool for sunk
    bool getSunkStatus() const; // returns true or false for sunk
    void isHit(); // increments hitCounter by 1 if ship is hit
    void setHitStatus(bool hitStatus); // can set bool for hit
    bool getHitStatus() const; // returns true or false for hit
    void setOrientation(string _orientation) throw(invalidOrientation,blankField); // H for horizontal, V for vertical
    bool checkHorizontal() const; // returns true if ship is horizontal, otherwise vertical
};

class Carrier:public WaterVehicle{
private:
    
public:
    Carrier();
    bool isSunk() const;
};
class BattleShip:public WaterVehicle{
private:
    
public:
    BattleShip();
    bool isSunk() const;
};
class Cruiser:public WaterVehicle{
private:
    
public:
    Cruiser();
    bool isSunk() const;
};
class Submarine:public WaterVehicle{
private:
    
public:
    Submarine();
    bool isSunk() const;
};
class Destroyer:public WaterVehicle{
private:
    
public:
    Destroyer();
    bool isSunk() const;
};

#endif /* WaterVehicle_h */
