//Tobby Lie 103385744
//CSCI 2312
//Final Project
//November 3, 2017
//Grid class prototypes

#ifndef Grid_h
#define Grid_h

#include "WaterVehicle.h"

class outOfBounds{
private:
    string name;
public:
    outOfBounds():name(""){}
    outOfBounds(string _name):name(_name){}
    void setName(string _name){name = _name;};
    string getName() const {return name;}
    void errorMessage(){
        cout << "Error: Ship " << name << " placement is out of bounds!" << endl;
        cout << "Program terminating." << endl;
        exit(0);
    }
};
class overlapcells{
public:
    void errorMessage(){
        cout << "Error: Ship overlaps another!" << endl;
        cout << "Program terminating." << endl;
        exit(0);
    }
};

const int rowSize = 10;
const int colSize = 10;
class Grid{
private:
    static const int ROWS = rowSize; // rows
    static const int COLS = colSize; // cols
    char board[ROWS][COLS];
public:
    Carrier c;
    BattleShip b;
    Cruiser cr;
    Destroyer d;
    Submarine s;
    void updateHitCounters();
    void setGuess(int _x, int _y);
    void checkGuess(int _x, int _y);
    char getBoardCell(int _x, int _y); // returns char from board space
    bool readFromFile(string fileName); // will read .csv files for ship info
    void printGrid() const;
    bool checkOrientationInput(string _horizOrVert) throw(invalidOrientation);
    void placeShip();
    void placeCarrier() throw(outOfBounds,overlapcells);
    void placeBattleShip() throw(outOfBounds,overlapcells);
    void placeCruiser() throw(outOfBounds,overlapcells);
    void placeDestroyer() throw(outOfBounds,overlapcells);
    void placeSubmarine() throw(outOfBounds,overlapcells);
    bool inBoundaries(int _x, int _y, int _length, bool _isHorizontal);
    bool overlap(int _x, int _y, int _length, bool _isHorizontal);
    void clearGrid();
    void randomShipPlacement();
    void randomCarrierPlacement();
    void randomCruiserPlacement();
    void randomDestroyerPlacement();
    void randomSubmarinePlacement();
    void randomBattleShipPlacement();
    string convertIntCoorToStr(int input);
    int convertStringCoorToInt(string input);
    bool checkShipStatus();
    bool checkCarrierStatus();
    bool checkCruiserStatus();
    bool checkDestroyerStatus();
    bool checkSubmarineStatus();
    bool checkBattleshipStatus();
    void resetHitFlags();
    void resetSunkFlags();
    void printGuessesGrid(Grid enemyGrid);
};

#endif /* Grid_h */



















