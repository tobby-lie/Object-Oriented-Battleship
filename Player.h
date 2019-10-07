//Tobby Lie 103385744
//CSCI 2312
//Final Project
//November 3, 2017
//Player class prototypes

#ifndef Player_h
#define Player_h

#include "Grid.h"

class Player{
public:
    Grid ownGrid;
    Grid guessesGrid;
    char userTorpedoInput(Player &enemy);
    bool xIsInRange(int _x);
    bool yIsInRange(int _y);// true if valid position, false if not
    bool overlap(int _x, int _y); // true if overlap, false if not
    void RandomTorpedoShot(Player &enemy);
    int convertCharToInt(char input);
    bool hasLost();
    void playGame();
};

#endif /* Player_h */
