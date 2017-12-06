#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include "ship.h"
#include "bomb.h"

using namespace std;

class Board {
	uint16_t num_of_rows, num_of_columns; // redundant info …
	vector<Ship> ships; // ships that are placed on the board
	vector<vector<int> > board; // each element indicates the index of a ship in the 'ships' vector
public:
	Board(const string &filename); // loads board from file 'filename'
	Board();
	bool launch_ship(Ship &ship); // adds ship to the board, if possible
	void move_ships(); // tries to randmonly move all the ships of the fleet
	bool attack(const Bomb &bomb);
	void display() const; // displays the colored board during the game
	void show() const; // shows the attributes of the board (for debugging)
	bool can_launch_ship(int column, int row, char direction, int size);
	vector<vector<int> > get_board() const { return board; }
	vector<Ship> get_ships() const { return ships; }
	size_t get_num_of_ships() { return ships.size(); };
	void create_board_file(string &fileName);
	uint16_t ships_destroyed() const;
};