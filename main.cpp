//Tobby Lie 103385744
//CSCI 2312
//Final Project
//November 3, 2017
//This program utilizes Object Oriented Programming
//to implement a battleship game with a user against a computer

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Player.h"

int main(){

    srand((int)time(NULL));
    
    // did the extra credit
    // game will tell user if shot was a miss, hit or sink
    // sinks require that entire length of a ship is hit
    Player game;
    game.playGame();

return 0;
}












