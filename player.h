#pragma once

#include <string>
#include <iostream>
#include <ctime>
#include <cctype>

#include "board.h"

using namespace std;

class Player {
	const string name; // player's name
	Board board; // player's board
public:
	Player(string playerName, Board &board);
	Player(string playerName, string boardFilename);
	void show_board() const; // shows the player’s board
	Bomb getBomb() const; // asks bomb target coordinates and creates the bomb
	string get_name() const { return name; }
	uint16_t ships_destroyed() const { return board.ships_destroyed(); };
	void board_attacked(const Bomb &bomb); // "receives" a bomb from the opponent;
	void show() const;
};