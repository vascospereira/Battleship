#pragma once

#include <string>
#include "symbolics.h"
#include <iostream>

using namespace std;

class Ship {
	char symbol; 
	PositionInt position; 
	char orientation; 
	unsigned size; 
	unsigned color; // color code: 0=BLACK, 1=BLUE
	string status; // status[i]: upper case = good; lower case = damaged
public:
	Ship(char symbol, PositionChar position, char orientation, unsigned size, unsigned color);
	char getSymbol() const{ return symbol; }
	PositionInt getPosition() const { return position; }
	char getOrientation() const { return orientation; }
	unsigned getSize() const { return size; }
	unsigned getColor() const { return color; }
	string getStatus() const { return status; }
	void setStatus(int i) { status[i] = tolower(status[i]); }
	void move(char direction, bool rotate); // moves the boat (SEE NOTES)
	//bool moveRand(unsigned int lineMin, unsigned int columnMin, unsigned int
	//lineMax, unsigned int columnMax); // moves the ship randomly
	bool attack(size_t ship_part); //partNumber = {0,1,…, size-1}
	bool isdestroyed() const; // checks whether the ship is destroyed
	void show() const; // shows the attributes of the ship (for debugging)
	
};