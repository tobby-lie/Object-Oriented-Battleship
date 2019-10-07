//Tobby Lie 103385744
//CSCI 2312
//Final Project
//November 3, 2017
//Grid class implementation

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cctype>
#include "Grid.h"

using namespace std;

// clears the grid by setting all board cells to blank space
void Grid::clearGrid(){
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS;j++){
            board[i][j] = ' ';
        } // end for
    } // end for
} // end clearGrid

// prints grid at current state, which may consist of blank space, x's and o's
void Grid::printGrid() const{
    cout << setw(2) << left << "  |A |B |C |D |E |F |G |H |I |J |" << endl;;
    for(int i = 0; i < ROWS; i++){
        cout << "---------------------------------" << endl;
        cout << setw(2) << left << i + 1 << "|";
        for(int j = 0; j < COLS; j++){
            cout << setw(2) << left << board[i][j] << "|";
        } // end for
        cout << endl;
    } // end for
} // end printGrid

// print guesses grid meaning, the opponents grid is passed as an argument and the guesses that are on that grid are then displayed but not the ship placement cells
void Grid::printGuessesGrid(Grid enemyGrid){
    cout << setw(2) << left << "  |A |B |C |D |E |F |G |H |I |J |" << endl;;
    for(int i = 0; i < ROWS; i++){
        cout << "---------------------------------" << endl;
        cout << setw(2) << left << i + 1 << "|";
        for(int j = 0; j < COLS; j++){
            if(enemyGrid.board[i][j] == 's'){
                enemyGrid.board[i][j] = ' ';
            } // end if
            cout << setw(2) << left << enemyGrid.board[i][j] << "|";
        } // end for
        cout << endl;
    } // end for
} // end printGuessesGrid

// returns the char of a specific board cell in which the x and y coordinates are passed in
char Grid::getBoardCell(int _x, int _y){
    return board[_y-1][_x-1];
} // end getBoardCell

// can set the cell specified by x and y to x or o
void Grid::setGuess(int _x, int _y){
    if(board[_y-1][_x-1] == 's'){
        board[_y-1][_x-1] = 'o';
    } // end if
    else{
        board[_y-1][_x-1] = 'x';
    } // end else
} // end setGuess

// go through length of each watervehicle and see if any new hits, if so increment hit counter
void Grid::updateHitCounters(){
    int tempCounter = 0;
    int _x = c.getLocation_x();
    int _y = c.getLocation_y();
    if(c.checkHorizontal() == true){ // is horizontal
        for(int i = 0; i < c.getLength(); i++){
            if(board[_y-1][_x-1] == 'o'){
                tempCounter++;
            } // end if
            _x++;
        } // end for
    } // end if
    else{
        for(int i = 0; i < c.getLength(); i++){
            if(board[_y-1][_x-1] == 'o'){
                tempCounter++;
            } // end if
            _y++;
        } // end for
    } // end else
    while(tempCounter > c.getHitCounter()){
        c.isHit(); // increment hit counter
    } // end while
} // end updateHitCounters

// takes information from file and initializes ships with info
bool Grid::readFromFile(string fileName){ // return true if successful read
    ifstream inFile;
    inFile.open(fileName.c_str());
    if(inFile.fail()){ // false if file read fails
        return false;
    } // end if
    string shipType, x_CoorStr, horizOrVertStr, y_CoorStr, location;
    // read header info in
    getline(inFile,shipType,',');
    getline(inFile,location,',');
    getline(inFile,horizOrVertStr);
    try{
        while(getline(inFile,shipType,',')){
            y_CoorStr = ""; // re-initialize coordinates to blank every loop
            x_CoorStr = "";
                if(shipType == ""){
                    throw blankField();
                } // end if
        
        for(int i = 0; i < (int)shipType.size(); i ++){
            shipType[i] = toupper(shipType[i]);
        } // end for
        // location and horizOrVertSTr
        getline(inFile,location,',');
        getline(inFile,horizOrVertStr);
        for(int i = 0; i < (int)location.size(); i++){
            location[i] = toupper(location[i]);
        } // end for
        //separate concatenated letter and number for x and y
        for(int i = 0; i < (int)location.size(); i++){
            if(isalpha(location[i])){// if is a char
                x_CoorStr = location[i];
            } // end if
            else if(isdigit(location[i])){
                y_CoorStr = location[i];
            } // end else if
        } // end for
        if(shipType == "CARRIER"){
            c.setTypeOfShip(shipType);
            c.setLocation_x(x_CoorStr); // may throw exception
            c.setLocation_y(y_CoorStr);
            c.setOrientation(horizOrVertStr);
        } // end if
        else if(shipType == "BATTLESHIP"){
            b.setTypeOfShip(shipType);
            b.setLocation_x(x_CoorStr); // may throw exception
            b.setLocation_y(y_CoorStr);
            b.setOrientation(horizOrVertStr);
        } // end else if
        else if(shipType == "CRUISER"){
            cr.setTypeOfShip(shipType);
            cr.setLocation_x(x_CoorStr); // may throw exception
            cr.setLocation_y(y_CoorStr);
            cr.setOrientation(horizOrVertStr);
        } // end else if
        else if(shipType == "DESTROYER"){
            d.setTypeOfShip(shipType);
            d.setLocation_x(x_CoorStr); // may throw exception
            d.setLocation_y(y_CoorStr);
            d.setOrientation(horizOrVertStr);
        } // end else if
        else if(shipType == "SUBMARINE"){
            s.setTypeOfShip(shipType);
            s.setLocation_x(x_CoorStr); // may throw exception
            s.setLocation_y(y_CoorStr);
            s.setOrientation(horizOrVertStr);
        } // end else if
        } // end while
    } // end try
    catch(invalidOrientation iOr){
        iOr.errorMessage();
    } // end catch
    catch(invalidX_Coor iX){
        iX.errorMessage();
    } // end catch
    catch(invalidY_Coor iY){
        iY.errorMessage();
    } // end catch
    catch(blankField b){
        b.errorMessage();
    } // end catch
    return true;
} // end readFromFile

// places all of the ships on the board
void Grid::placeShip(){
    try{ // may throw exceptions
        placeCarrier();
        placeBattleShip();
        placeCruiser();
        placeDestroyer();
        placeSubmarine();
    } // end try
    catch(outOfBounds o){
        string temp = o.getName();
        cout << "Error: Ship " << temp << " placement is out of bounds!" << endl;
        cout << "Program terminating." << endl;
        exit(0);
    } // end catch
    catch(overlapcells ov){
        ov.errorMessage();
    } // end catch
} // end placeShip

// board placement for carrier
void Grid::placeCarrier() throw(outOfBounds,overlapcells){
    int _x = c.getLocation_x();
    int _y = c.getLocation_y();

    if((inBoundaries(c.getLocation_x(),c.getLocation_y(),c.getLength(),c.checkHorizontal())) == false){
        throw outOfBounds(c.getTypeOfShip());
    } // end if
    if((overlap(c.getLocation_x(), c.getLocation_y(), c.getLength(), c.checkHorizontal()))){
        throw overlapcells();
    } // end if
    else{
        if(c.checkHorizontal() == true){
            for(int i = 0; i < c.getLength(); i++){
                board[_y - 1][_x - 1] = 's';
                _x++;
            } // end for
        } // end if
        else{
            for(int i = 0; i < c.getLength(); i++){
                board[_y - 1][_x - 1] = 's';
                _y++;
            } // end for
        } // end else
    } // end else
} // end placeCarrier

// board placement for battleship
void Grid::placeBattleShip() throw(outOfBounds,overlapcells){
    int _x = b.getLocation_x();
    int _y = b.getLocation_y();

    if((inBoundaries(b.getLocation_x(),b.getLocation_y(),b.getLength(),b.checkHorizontal())) == false){
        throw outOfBounds(b.getTypeOfShip());
    } // end if
    if((overlap(b.getLocation_x(), b.getLocation_y(), b.getLength(), b.checkHorizontal()))){
        throw overlapcells();
    } // end if
    else{
        if(b.checkHorizontal() == true){
            for(int i = 0; i < b.getLength(); i++){
                board[_y - 1][_x - 1] = 's';
                _x++;
            } // end for
        } // end if
        else{
            for(int i = 0; i < b.getLength(); i++){
                board[_y - 1][_x - 1] = 's';
                _y++;
            } // end for
        } // end else
    } // end else
} // end placeBattleShip

// board placement for destroyer
void Grid::placeDestroyer() throw(outOfBounds, overlapcells){
    int _x = d.getLocation_x();
    int _y = d.getLocation_y();

    if((inBoundaries(d.getLocation_x(),d.getLocation_y(),d.getLength(),d.checkHorizontal())) == false){
        throw outOfBounds(d.getTypeOfShip());
    } // end if
    if((overlap(d.getLocation_x(), d.getLocation_y(), d.getLength(), d.checkHorizontal()))){
        throw overlapcells();
    } // end if
    else{
        if(d.checkHorizontal() == true){
            for(int i = 0; i < d.getLength(); i++){
                board[_y - 1][_x - 1] = 's';
                _x++;
            } // end for
        } // end if
        else{
            for(int i = 0; i < d.getLength(); i++){
                board[_y - 1][_x - 1] = 's';
                _y++;
            } // end for
        } // end else
    } // end else
} // end placeDestroyer

// board placement for cruiser
void Grid::placeCruiser() throw(outOfBounds, overlapcells){
    int _x = cr.getLocation_x();
    int _y = cr.getLocation_y();

    if((inBoundaries(cr.getLocation_x(),cr.getLocation_y(),cr.getLength(),cr.checkHorizontal())) == false){
        throw outOfBounds(cr.getTypeOfShip());
    } // end if
    if((overlap(cr.getLocation_x(), cr.getLocation_y(), cr.getLength(),cr.checkHorizontal()))){
        throw overlapcells();
    } // end if
    else{
        if(cr.checkHorizontal() == true){
            for(int i = 0; i < cr.getLength(); i++){
                board[_y - 1][_x - 1] = 's';
                _x++;
            } // end for
        } // end if
        else{
            for(int i = 0; i < cr.getLength(); i++){
                board[_y - 1][_x - 1] = 's';
                _y++;
            } // end for
        } // end else
    } // end else
} // end placeCruiser

// board placement for submarine
void Grid::placeSubmarine() throw(outOfBounds, overlapcells){
    int _x = s.getLocation_x();
    int _y = s.getLocation_y();

    if((inBoundaries(s.getLocation_x(),s.getLocation_y(),s.getLength(),s.checkHorizontal())) == false){
        throw outOfBounds(s.getTypeOfShip());
    } // end if
    if((overlap(s.getLocation_x(), s.getLocation_y(), s.getLength(), s.checkHorizontal()))){
        throw overlapcells();
    } // end if
    else{
        if(s.checkHorizontal() == true){
            for(int i = 0; i < s.getLength(); i++){
                board[_y - 1][_x - 1] = 's';
                _x++;
            } // end for
        } // end if
        else{
            for(int i = 0; i < s.getLength(); i++){
                board[_y - 1][_x - 1] = 's';
                _y++;
            } // end for
        } // end else
    } // end else
} // end placeSubmarine

// returns true if board cell is already occupied
bool Grid::overlap(int _x, int _y, int _length, bool _isHorizontal){
    if(_isHorizontal) {
        for(int i = 0; i < _length; i++){
            if(board[_y - 1][_x - 1] == 's'){
                return true;
            } // end if
            _x++;
        } // end for
    } // end if
    else{
        for(int i = 0; i < _length; i++){
            if(board[_y - 1][_x - 1] != ' '){
                return true;
            } // end if
            _y++;
        } // end for
    } // end else
    return false;
} // end overlap

// returns true if in boundaries, and false if not
bool Grid::inBoundaries(int _x, int _y, int _length, bool _isHorizontal){
    if(_isHorizontal){
        for(int i = 0; i < _length; i++){
            if(_x > 10){
                return false;
            } // end if
            _x++;
        } // end for
    } // end if
    else{
        for(int i = 0; i < _length; i++){
            if(_y > 10){
                return false;
            } // end if
        _y++;
        } // end for
    } // end else
    return true;
} // end inBoundaries

// randomly generates ship placement for opponent ships
void Grid::randomShipPlacement(){
    randomCarrierPlacement();
    randomCruiserPlacement();
    randomDestroyerPlacement();
    randomSubmarinePlacement();
    randomBattleShipPlacement();
} // end randomShipPlacement

// converts int input to string values based on defined grid coordinates A-J
string Grid::convertIntCoorToStr(int input){
    switch (input) {
        case 1:
            return "A";
            break;
        case 2:
            return "B";
            break;
        case 3:
            return "C";
            break;
        case 4:
            return "D";
            break;
        case 5:
            return "E";
            break;
        case 6:
            return "F";
            break;
        case 7:
            return "G";
            break;
        case 8:
            return "H";
            break;
        case 9:
            return "I";
            break;
        case 10:
            return "J";
            break;
        default:
            return "X";
            break;
    } // end switch
} // end convertIntCoorToStr

// random board placement for carrier
void Grid::randomCarrierPlacement(){
    int _x = 0;
    int _y = 0;
    string _xStr = " ";
    string _yStr= " ";
    stringstream ss;
    int hOrV = 0;
    do{
        _x = (rand()%10)+1;
        _y = (rand()%10)+1;
        hOrV = (rand()%10)+1;
        if(hOrV < 5){
            c.setOrientation("H");
        } // end if
        else if(hOrV > 5){
            c.setOrientation("V");
        } // end else if
    }while((overlap(_x,_y,c.getLength(),c.checkHorizontal()) == true) || !(inBoundaries(_x, _y,c.getLength(),c.checkHorizontal())));
    // end do while
    _xStr = convertIntCoorToStr(_x);
    ss << _y; // use stringstream in order to convert int to string
    // initialize
    c.setLocation_x(_xStr);
    c.setLocation_y(ss.str());
    ss.clear();
    c.setTypeOfShip("Carrier");
    
    if(c.checkHorizontal() == true){
        for(int i = 0; i < c.getLength(); i++){
            board[_y - 1][_x - 1] = 's';
            _x++;
        } // end for
    } // end if
    else{
        for(int i = 0; i < c.getLength(); i++){
            board[_y - 1][_x - 1] = 's';
            _y++;
        } // end for
    } // end else
} // end randomCarrierPlacement

// random board placement for cruiser
void Grid::randomCruiserPlacement(){
    int _x = 0;
    int _y = 0;
    string _xStr = " ";
    string _yStr= " ";
    stringstream ss;
    int hOrV = 0;
    do{
        _x = (rand()%10)+1;
        _y = (rand()%10)+1;
        hOrV = (rand()%10)+1;
        if(hOrV < 5){
            cr.setOrientation("H");
        } // end if
        else if(hOrV > 5){
            cr.setOrientation("V");
        } // end else if
        
    }while((overlap(_x,_y,cr.getLength(),cr.checkHorizontal()) == true) || !(inBoundaries(_x, _y,cr.getLength(),cr.checkHorizontal())));
    // end do while
    _xStr = convertIntCoorToStr(_x);
    ss << _y; // use stringstream in order to convert int to string
    // initialize
    cr.setLocation_x(_xStr);
    cr.setLocation_y(ss.str());
    ss.clear();
    cr.setTypeOfShip("Cruiser");
    
    if(cr.checkHorizontal() == true){
        for(int i = 0; i < cr.getLength(); i++){
            board[_y - 1][_x - 1] = 's';
            _x++;
        } // end for
    } // end if
    else{
        for(int i = 0; i < cr.getLength(); i++){
            board[_y - 1][_x - 1] = 's';
            _y++;
        } // end for
    } // end else
} // end randomCruiserPlacement

// random board placement for destroyer
void Grid::randomDestroyerPlacement(){
    int _x = 0;
    int _y = 0;
    string _xStr = " ";
    string _yStr= " ";
    stringstream ss;
    int hOrV = 0;
    do{
        _x = (rand()%10)+1;
        _y = (rand()%10)+1;
        hOrV = (rand()%10)+1;
        if(hOrV < 5){
            d.setOrientation("H");
        } // end if
        else if(hOrV > 5){
            d.setOrientation("V");
        } // end else if
    }while((overlap(_x,_y,d.getLength(),d.checkHorizontal()) == true) || !(inBoundaries(_x, _y,d.getLength(),d.checkHorizontal())));
     // end do while
    _xStr = convertIntCoorToStr(_x);
    ss << _y; // use stringstream in order to convert int to string
    // initialize
    d.setLocation_x(_xStr);
    d.setLocation_y(ss.str());
    ss.clear();
    d.setTypeOfShip("Destroyer");
    
    if(d.checkHorizontal() == true){
        for(int i = 0; i < d.getLength(); i++){
            board[_y - 1][_x - 1] = 's';
            _x++;
        } // end for
    } // end if
    else{
        for(int i = 0; i < d.getLength(); i++){
            board[_y - 1][_x - 1] = 's';
            _y++;
        } // end for
    } // end else
} // end randomDestroyerPlacment

// random board placement for submarine
void Grid::randomSubmarinePlacement(){
    int _x = 0;
    int _y = 0;
    string _xStr = " ";
    string _yStr= " ";
    stringstream ss;
    int hOrV = 0;
    do{
        _x = (rand()%10)+1;
        _y = (rand()%10)+1;
        hOrV = (rand()%10)+1;
        if(hOrV < 5){
            s.setOrientation("H");
        } // end if
        else if(hOrV > 5){
            s.setOrientation("V");
        } // end else if
    }while((overlap(_x,_y,s.getLength(),s.checkHorizontal()) == true) || !(inBoundaries(_x, _y,s.getLength(),s.checkHorizontal())));
    // end do while
    _xStr = convertIntCoorToStr(_x);
    ss << _y; // use stringstream in order to convert int to string
    // initialize
    s.setLocation_x(_xStr);
    s.setLocation_y(ss.str());
    ss.clear();
    s.setTypeOfShip("Submarine");
    
    if(s.checkHorizontal() == true){
        for(int i = 0; i < s.getLength(); i++){
            board[_y - 1][_x - 1] = 's';
            _x++;
        } // end for
    } // end if
    else{
        for(int i = 0; i < s.getLength(); i++){
            board[_y - 1][_x - 1] = 's';
            _y++;
        } // end for
    } // end else
} // end randomSubmarinePlacement

// random board placement for battleship
void Grid::randomBattleShipPlacement(){
    int _x = 0;
    int _y = 0;
    string _xStr = " ";
    string _yStr= " ";
    stringstream ss;
    int hOrV = 0;
    do{
        _x = (rand()%10)+1;
        _y = (rand()%10)+1;
        hOrV = (rand()%10)+1;
        if(hOrV < 5){
            b.setOrientation("H");
        } // end if
        else if(hOrV > 5){
            b.setOrientation("V");
        } // end else if
    }while((overlap(_x,_y,b.getLength(),b.checkHorizontal()) == true) || !(inBoundaries(_x, _y,b.getLength(),b.checkHorizontal())));
    // end do while
    _xStr = convertIntCoorToStr(_x);
    ss << _y; // use stringstream in order to convert int to string
    // initialize
    b.setLocation_x(_xStr);
    b.setLocation_y(ss.str());
    ss.clear();
    b.setTypeOfShip("BattleShip");
    
    if(b.checkHorizontal() == true){
        for(int i = 0; i < b.getLength(); i++){
            board[_y - 1][_x - 1] = 's';
            _x++;
        } // end for
    } // end if
    else{
        for(int i = 0; i < b.getLength(); i++){
            board[_y - 1][_x - 1] = 's';
            _y++;
        } // end for
    } // end else
} // end randomBattleshipPlacement

// resets all hit flags to false
void Grid::resetHitFlags(){
    c.setHitStatus(false);
    cr.setHitStatus(false);
    d.setHitStatus(false);
    b.setHitStatus(false);
    s.setHitStatus(false);
} // end resetHitFlags

// reset all sink flags to false and hit counters to 0
void Grid::resetSunkFlags(){
    c.setSunkStatus(false);
    cr.setSunkStatus(false);
    d.setSunkStatus(false);
    b.setSunkStatus(false);
    s.setSunkStatus(false);
    
    c.setHitCounter(0);
    cr.setHitCounter(0);
    d.setHitCounter(0);
    b.setHitCounter(0);
    s.setHitCounter(0);
} // end resetSunkFlags

// checks ship status for hit or not
bool Grid::checkShipStatus(){ // will return true if any hits occur
    bool hitStatus = false;
    
    if(checkCarrierStatus() == true){
        hitStatus = true;
    } // end if
    if(checkCruiserStatus() == true){
        hitStatus = true;
    } // end if
    if(checkDestroyerStatus() == true){
        hitStatus = true;
    } // end if
    if(checkSubmarineStatus() == true){
        hitStatus = true;
    } // end if
    if(checkBattleshipStatus() == true){
        hitStatus = true;
    } // end if
    return hitStatus;
} // end checkShipStatus

// check hit and sunk status of carrier
bool Grid::checkCarrierStatus(){
    int tempCounter = 0;
    int x = c.getLocation_x();
    int y = c.getLocation_y();
    bool shipAffected = false;
    if(c.checkHorizontal() == true){
    for(int i = 0; i < c.getLength(); i++){
        if(board[y-1][x-1] == 'o'){
                tempCounter++;
        } // end if
        x++;
    } // end for
    } // end if
    else{
        for(int i = 0; i < c.getLength(); i++){
            if(board[y-1][x-1] == 'o'){
                tempCounter++;
            } // end if
        y++;
        } // end for
    } // end else
    if(tempCounter > c.getHitCounter()){
        c.isHit();// increment
        c.setHitStatus(true);
    } // end if
    if(c.getHitStatus() == true && c.isSunk() == false){
        cout << "The Carrier has been hit!" << endl;
        shipAffected = true;
    } // end if
    else if(c.isSunk()){
        cout << "The Carrier has been sunk!" << endl;
        shipAffected = true;
    } // end else if
    return shipAffected;
} // end checkCarrierStatus

// check hit and sunk status of cruiser
bool Grid::checkCruiserStatus(){
    int tempCounter = 0;
    int x = cr.getLocation_x();
    int y = cr.getLocation_y();
    bool shipAffected = false;
    if(cr.checkHorizontal() == true){
        for(int i = 0; i < cr.getLength(); i++){
            if(board[y-1][x-1] == 'o'){
                tempCounter++;
            } // end if
        x++;
        } // end for
    } // end if
    else{
        for(int i = 0; i < cr.getLength(); i++){
            if(board[y-1][x-1] == 'o'){
                tempCounter++;
            } // end if
        y++;
        } // end for
    } // end else
    if(tempCounter > cr.getHitCounter()){
        cr.isHit();// increment
        cr.setHitStatus(true);
    } // end if
    if(cr.getHitStatus() == true && cr.isSunk() == false){
        cout << "The Cruiser has been hit!" << endl;
        shipAffected = true;
    } // end if
    else if(cr.isSunk()){
        cout << "The Cruiser has been sunk!" << endl;
        shipAffected = true;
    } // end else if
    return shipAffected;
} // end checkCruiserStatus

// check hit and sunk status of destroyer
bool Grid::checkDestroyerStatus(){
    int tempCounter = 0;
    int x = d.getLocation_x();
    int y = d.getLocation_y();
    bool shipAffected = false;
    if(d.checkHorizontal() == true){
        for(int i = 0; i < d.getLength(); i++){
            if(board[y-1][x-1] == 'o'){
                tempCounter++;
            } // end if
        x++;
        } // end for
    } // end if
    else{
        for(int i = 0; i < d.getLength(); i++){
            if(board[y-1][x-1] == 'o'){
                tempCounter++;
            } // end if
        y++;
        } // end for
    } // end else
    if(tempCounter > d.getHitCounter()){
        d.isHit();// increment
        d.setHitStatus(true);
    } // end if
    if(d.getHitStatus() == true && d.isSunk() == false){
        cout << "The Destroyer has been hit!" << endl;
        shipAffected = true;
    } // end if
    else if(d.isSunk()){
        cout << "The Destroyer has been sunk!" << endl;
        shipAffected = true;
    } // end else if
    return shipAffected;
} // end checkDestroyerStatus

// check hit and sunk status of submarine
bool Grid::checkSubmarineStatus(){
    int tempCounter = 0;
    int x = s.getLocation_x();
    int y = s.getLocation_y();
    bool shipAffected = false;
    if(s.checkHorizontal() == true){
        for(int i = 0; i < s.getLength(); i++){
            if(board[y-1][x-1] == 'o'){
                tempCounter++;
            } // end if
        x++;
        } // end for
    } // end if
    else{
        for(int i = 0; i < s.getLength(); i++){
            if(board[y-1][x-1] == 'o'){
                tempCounter++;
            } // end if
        y++;
        } // end for
    } // end else
    if(tempCounter > s.getHitCounter()){
        s.isHit();// increment
        s.setHitStatus(true);
    } // end if
    if(s.getHitStatus() == true && s.isSunk() == false){
        cout << "The Submarine has been hit!" << endl;
        shipAffected = true;
    } // end if
    else if(s.isSunk()){
        cout << "The Submarine has been sunk!" << endl;
        shipAffected = true;
    } // end else if
    return shipAffected;
} // end checkSubmarineStatus

// check hit and sunk status of battleship
bool Grid::checkBattleshipStatus(){
    int tempCounter = 0;
    int x = b.getLocation_x();
    int y = b.getLocation_y();
    bool shipAffected = false;
    if(b.checkHorizontal() == true){
        for(int i = 0; i < b.getLength(); i++){
            if(board[y-1][x-1] == 'o'){
                tempCounter++;
            } // end if
        x++;
        } // end for
    } // end if
    else{
        for(int i = 0; i < b.getLength(); i++){
            if(board[y-1][x-1] == 'o'){
                tempCounter++;
            } // end if
        y++;
        } // end for
    } // end else
    if(tempCounter > b.getHitCounter()){
        b.isHit();// increment
        b.setHitStatus(true);
    } // end if
    if(b.getHitStatus() == true && b.isSunk() == false){
        cout << "The Battleship has been hit!" << endl;
        shipAffected = true;
    } // end if
    else if(b.isSunk()){
        cout << "The Battleship has been sunk!" << endl;
        shipAffected = true;
    } // end else if
    return shipAffected;
} // end checkBattleShipStatus
