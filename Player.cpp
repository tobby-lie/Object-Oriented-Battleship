//Tobby Lie 103385744
//CSCI 2312
//Final Project
//November 3, 2017
//Player class implementation

#include <cctype>
#include <iostream>
#include <sstream>
#include "Player.h"

using namespace std;

// user provides x and y coordinates to be placed on enemy board that is passed in
char Player::userTorpedoInput(Player &enemy){
    char choice;
    cout << "You may quit by inputting Q, input any other key to continue: " << endl;
    cin >> choice;
    choice = toupper(choice);
    if(choice == 'Q'){
        return choice;
    } // end if
    char _x = ' ';
    int _xInt = 0;
    int yInt = 0;
    do{
    cout << "Please input a letter A-J for an x coordinate " << endl;
    cin >> _x;
    _x = toupper(_x);
    if(_x == 'Q'){
        return _x;
    } // end if
    _xInt = convertCharToInt(_x);
    while((xIsInRange(_xInt)) == false && (convertCharToInt(_x)) == -1){
        cout << "Invalid input! Please input a letter A-J for an x coordinate " << endl;
        cin >> _x;
        _x = toupper(_x);
        if(_x == 'Q'){
            return _x;
        } // end if
        _xInt = convertCharToInt(_x);
    } // end while
    cout << "Please input a number 1-10 for a y coordinate " << endl;
    cin >> yInt;
    while((yIsInRange(yInt)) == false || cin.fail()){
        cout << "Invalid input! Please input a number 1-10 for a y coordinate " << endl;
        cin.clear();
        cin.ignore();
        cin >> yInt;
    } // end while
    if(overlap(_xInt, yInt)){
        cout << "This position has already been tried! Try again." << endl;
    } // end if
        
    }while(overlap(_xInt, yInt)); // end do while
    
    guessesGrid.setGuess(_xInt, yInt); // mark x on guesses grid
    enemy.ownGrid.setGuess(_xInt, yInt); // also mark x on enemy's own grid
    
    return 'Y';
} // end userTorpedoInput

// randomises torpedoshots for enemy board passed in
void Player::RandomTorpedoShot(Player &enemy){
    int x = (rand()%10)+1;
    int y = (rand()%10)+1;
    while(overlap(x, y) == true){ // keep generating until spot guessed is not already tried
        x = (rand()%10)+1;
        y = (rand()%10)+1;
    } // end while
    
    guessesGrid.setGuess(x, y); // mark x on guesses grid
    enemy.ownGrid.setGuess(x, y); // also mark x on enemy's own grid
} // end RandomTorpedoShot

// converts a char input to designated int on defined board coordinate system
int Player::convertCharToInt(char input){
    switch (input) {
        case 'A':
            return 1;
            break;
        case 'B':
            return 2;
            break;
        case 'C':
            return 3;
            break;
        case 'D':
            return 4;
            break;
        case 'E':
            return 5;
            break;
        case 'F':
            return 6;
            break;
        case 'G':
            return 7;
            break;
        case 'H':
            return 8;
            break;
        case 'I':
            return 9;
            break;
        case 'J':
            return 10;
            break;
        default:
            return -1;
            break;
    } // end switch
} // end convertCharToInt

// checks if placement is taken and is overlapped
bool Player::overlap(int _x, int _y){
    if(guessesGrid.getBoardCell(_x, _y) == 'x' || guessesGrid.getBoardCell(_x, _y) == 'o'){
        return true;
    } // end if
    else{
        return false;
    } // end else
} // end overlap

// checks if int is in range of board coordinates
bool Player::yIsInRange(int _y){
    if(_y < 0 || _y > 10){
        return false;
    } // end if
    else{
        return true;
    } // end else
} // end yIsInRange

// makes sure x input is within range
bool Player::xIsInRange(int _x){
    if(_x < 0 || _x > 10){
        return false;
    } // end if
    else{
        return true;
    } // end else
} // end xIsInRange

// checks if all ships are sunk
bool Player::hasLost(){
    int shipSunkCounter = 0;
    if(ownGrid.c.isSunk() == true){
        shipSunkCounter++;
    } // end if
    if(ownGrid.cr.isSunk() == true){
        shipSunkCounter++;
    } // end if
    if(ownGrid.d.isSunk() == true){
        shipSunkCounter++;
    } // end if
    if(ownGrid.b.isSunk() == true){
        shipSunkCounter++;
    } // end if
    if(ownGrid.s.isSunk() == true){
        shipSunkCounter++;
    } // end if
    if(shipSunkCounter == 5){
        return true;
    } // end if
    return false;
} // end hasLost

// game loop
void Player::playGame(){
    
    Player p;
    Player cpu;
    string fileName;
    char choice = 'Y';
    
    do{
        cout << endl;
        cout << "**************************" << endl;
        cout << "*                        *" << endl;
        cout << "* Welcome to BattleShip! *" << endl;
        cout << "*                        *" << endl;
        cout << "**************************" << endl;
        cout << "                          " << endl;
        cout << "       EXTRA CREDIT       " << endl;
        cout << "         COMPLETE         " << endl;
        cout << "  In order to fully sink  " << endl;
        cout << " a ship it's entire length" << endl;
        cout << "       must be hit        " << endl;
        cout << "                          " << endl;
        cout << "**************************" << endl;
        cout << endl;
        cout << "Please enter the name of the ship placement file (include the extension): " << endl;
        cin >> fileName;
        
        while(p.ownGrid.readFromFile(fileName.c_str()) == false){
            cout << endl;
            cout << "* Failed to open file! *" << endl;
            cout << "Try entering a file name again (include the extension): " << endl;
            cout << endl;
            cin >> fileName;
        } // end while
        
        p.ownGrid.clearGrid();
        p.guessesGrid.clearGrid();
        p.ownGrid.placeShip();
        cpu.ownGrid.clearGrid();
        cpu.ownGrid.randomShipPlacement();
        p.ownGrid.resetHitFlags();
        cpu.ownGrid.resetHitFlags();
        p.ownGrid.resetSunkFlags();
        cpu.ownGrid.resetSunkFlags();
        cout << "----------------------" << endl;
        cout << "      Player grid     " << endl;
        cout << "----------------------" << endl;
        p.ownGrid.printGrid();
        cout << "----------------------" << endl;
        cout << "     Player guesses   " << endl;
        cout << "----------------------" << endl;
        p.ownGrid.printGuessesGrid(cpu.ownGrid);
        while(p.hasLost() == false && cpu.hasLost() == false && choice != 'Q'){
            
            choice = p.userTorpedoInput(cpu);
            cpu.RandomTorpedoShot(p);
            
            cout << "----------------------" << endl;
            cout << "      Player grid     " << endl;
            cout << "----------------------" << endl;
            p.ownGrid.printGrid();
            cout << "----------------------" << endl;
            cout << "     Player guesses   " << endl;
            cout << "----------------------" << endl;
            p.ownGrid.printGuessesGrid(cpu.ownGrid);
            cout << "----------------------" << endl;
            cout << "Player Status Report: " << endl;
            cout << "----------------------" << endl;
            p.ownGrid.checkShipStatus();
            cout << "----------------------" << endl;
            p.ownGrid.resetHitFlags();
            cout << "CPU Status Report: " << endl;
            cout << "----------------------" << endl;
            cpu.ownGrid.checkShipStatus();
            cout << "----------------------" << endl;
            cpu.ownGrid.resetHitFlags();
        
        } // end while
        if(choice == 'Q'){
            cout << "***************************" << endl;
            cout << "*                         *" << endl;
            cout << "* You have quit the game! *" << endl;
            cout << "* Here is a game report:  *" << endl;
            cout << "*                         *" << endl;
            cout << "***************************" << endl;
            cout << endl;
            
            cout << "----------------------" << endl;
            cout << "      Player grid     " << endl;
            cout << "----------------------" << endl;
            p.ownGrid.printGrid();
            cout << "----------------------" << endl;
            cout << "     Player guesses   " << endl;
            cout << "----------------------" << endl;
            p.ownGrid.printGuessesGrid(cpu.ownGrid);
            cout << "----------------------" << endl;
            cout << "        CPU grid      " << endl;
            cout << "----------------------" << endl;
            cpu.ownGrid.printGrid();
            cout << "----------------------" << endl;
            cout << "Player Status Report: " << endl;
            cout << "----------------------" << endl;
            p.ownGrid.checkShipStatus();
            cout << "----------------------" << endl;
            p.ownGrid.resetHitFlags();
            cout << "CPU Status Report: " << endl;
            cout << "----------------------" << endl;
            cpu.ownGrid.checkShipStatus();
            cout << "----------------------" << endl;
            cpu.ownGrid.resetHitFlags();
        } // end if
        if(choice != 'Q'){
            if(cpu.hasLost() == true){
                cout << endl;
                cout << "* Player has won the game! *" << endl;
                cout << endl;
                exit(0);
            } // end if
            else if(cpu.hasLost() == false){
                cout << endl;
                cout << "* CPU has won the game! *" << endl;
                cout << endl;
                exit(0);
            } // end else if
        } // end if
    }while(choice != 'Q'); // end do while
} // end playGame
