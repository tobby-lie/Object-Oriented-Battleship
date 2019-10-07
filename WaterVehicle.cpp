//Tobby Lie 103385744
//CSCI 2312
//Final Project
//November 3, 2017
//WaterVehicle class implementation

#include "WaterVehicle.h"

// default constructor
WaterVehicle::WaterVehicle():startLocation_x(0),startLocation_y(0),sunk(false),hit(false),isHorizontal(true){} // end WaterVehicle

// overloaded constructor
WaterVehicle::WaterVehicle(int _x, int _y, bool _sunk, bool _hit, bool _isHorizontal):startLocation_x(_x), startLocation_y(_y), sunk(_sunk), hit(_hit), isHorizontal(_isHorizontal){} // end WaterVehicle

// setter for type of ship
void WaterVehicle::setTypeOfShip(string _typeOfShip){
    typeOfShip = _typeOfShip;
} // end setTypeOfShip

// return type of ship
string WaterVehicle::getTypeOfShip() const{
    return typeOfShip;
} // end getTypeOfShip

// setter for length
void WaterVehicle::setLength(int _length){
    length = _length;
} // end setLength

// return length
int WaterVehicle::getLength() const{
    return length;
} // end getLength

// setter for location_x
void WaterVehicle::setLocation_x(string _x) throw(invalidX_Coor,blankField){
    if(_x == ""){
        throw blankField();
    } // end if
    // need to get rid of possible spaces
    for(int i = 0; i < _x.size(); i++){
        if(!(isalnum(_x[i]))) {
            _x.erase(i--,1);
        } // end if
    } // end for
    char temp = _x[0];
    switch (temp) {
        case 'A':{
            startLocation_x = 1;
            return;
            break;
        }
        case 'B':{
            startLocation_x = 2;
            return;
            break;
        }
        case 'C':{
            startLocation_x = 3;
            return;
            break;
        }
        case 'D':{
            startLocation_x = 4;
            return;
            break;
        }
        case 'E':{
            startLocation_x = 5;
            return;
            break;
        }
        case 'F':{
            startLocation_x = 6;
            return;
            break;
        }
        case 'G':{
            startLocation_x = 7;
            return;
            break;
        }
        case 'H':{
            startLocation_x = 8;
            return;
            break;
        }
        case 'I':{
            startLocation_x = 9;
            return;
            break;
        }
        case 'J':{
            startLocation_x =  10;
            return;
            break;
        }
    } // end switch
    throw invalidX_Coor(); // if not within A - J
} // end setLocation_x

// return startLocation_x
int WaterVehicle::getLocation_x() const{
    return startLocation_x;
} // end getLocation_x

// setter for location_y
void WaterVehicle::setLocation_y(string _y) throw(invalidY_Coor,blankField){
    if(_y == ""){
        throw blankField();
    } // end if
    for(int i = 0; i < _y.size(); i++){
        if(!(isalnum(_y[i])) && _y[i] != '-') { // must make sure negative signs are preserved
            _y.erase(i--,1);
        } // end if
    } // end for
    
    int Yint = stoi(_y);
    
    if(Yint < 1 || Yint > 10){
        throw invalidY_Coor();
    } // end if
    else{
        startLocation_y = Yint;
    } // end else
} // end setLocation_y

// returns startLocation_y
int WaterVehicle::getLocation_y() const{
    return startLocation_y;
} // end getLocation_y

// setter for sunk
void WaterVehicle::setSunkStatus(bool sunkStatus){
    sunk = sunkStatus;
} // end setSunkStatus

// returns sunk
bool WaterVehicle::getSunkStatus() const{
    return sunk;
} // end getSunkStatus

// increments hitcounter
void WaterVehicle::isHit(){
    hitCounter++;
} // end isHit

// setter for hit status
void WaterVehicle::setHitStatus(bool hitStatus){
    hit = hitStatus;
} // end setHitStatus

// returns hit
bool WaterVehicle::getHitStatus() const{
    return hit;
} // end getHitStatus

// sets orientation of ship
void WaterVehicle::setOrientation(string _orientation) throw(invalidOrientation,blankField){
    if(_orientation == ""){
        throw blankField();
    } // end if
    for(int i = 0; i < _orientation.size(); i++){
        if(!(isalnum(_orientation[i]))) {
            _orientation.erase(i--,1);
        } // end if
    } // end for
    _orientation[0] = toupper(_orientation[0]);
    
    if(_orientation[0] != 'H' && _orientation[0] != 'V'){
        throw invalidOrientation();
    } // end if
    
    if(_orientation[0] == 'H'){
        isHorizontal = true;
    } // end if
    else{
        isHorizontal = false;
    } // end else
} // end setOrientation

// checks orientation of ship
bool WaterVehicle::checkHorizontal() const{
    if(isHorizontal){
        return true;
    } // end if
    else{
        return false;
    } // end else
} // end checkHorizontal

// sets the hitcounter to value passed in
void WaterVehicle::setHitCounter(int count){
    hitCounter = count;
} // end setHitCounter

// returns hit counter
int WaterVehicle::getHitCounter() const{
    return hitCounter;
} // end getHitCounter

// returns sunk status
bool WaterVehicle::isSunk() const{
    if(hitCounter == length){
        return true;
    } // end if
    return false;
} // end isSunk

// checks if carrier sunk
bool Carrier::isSunk() const{
    if(getHitCounter() == 5){
        return true;
    } // end if
    return false;
} // end isSunk

// checks if cruiser sunk
bool Cruiser::isSunk() const{
    if(getHitCounter() == 3){
        return true;
    } // end if
    return false;
} // end isSunk

// checks if destroyer sunk
bool Destroyer::isSunk() const{
    if(getHitCounter() == 2){
        return true;
    } // end if
    return false;
} // end isSunk

// check if battleship sunk
bool BattleShip::isSunk() const{
    if(getHitCounter() == 4){
        return true;
    } // end if
    return false;
} // end isSunk

// check if submarine sunk
bool Submarine::isSunk() const{
    if(getHitCounter() == 3){
        return true;
    } // end if
    return false;
} // end isSunk

// carrier constructor
Carrier::Carrier():WaterVehicle(){
    setTypeOfShip("Carrier"); // manually set type of ship
    setLength(5); // need to manually set length since it is predefined for each type of water vehicle
} // end Carrier

// battleship constructor
BattleShip::BattleShip():WaterVehicle(){
    setTypeOfShip("BattleShip");
    setLength(4);
} // end BattleShip

// cruiser constructor
Cruiser::Cruiser():WaterVehicle(){
    setTypeOfShip("Cruiser");
    setLength(3);
} // end Cruiser

// submarine constructor
Submarine::Submarine():WaterVehicle(){
    setTypeOfShip("Submarine");
    setLength(3);
} // end Submarine

// destroyer constructor
Destroyer::Destroyer():WaterVehicle(){
    setTypeOfShip("Destroyer");
    setLength(2);
} // end Destroyer
