#pragma once

/*Standard board size */

#define STANDARD_BOARD 10

#define AUTOMATIC true
#define MANUAL false

#define HORIZONTAL true
#define VERTICAL false

/*color code*/

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

/* Random directions */

#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3

struct PositionChar // to store a board position in char format
{ 
	char row, column; // ranges: lin - ['A'..'Z']; col - ['a'..'z']
};

struct PositionInt // to store a board position in unsig. integer format
{ // example: 7,0
	unsigned int lin, col; // ranges: lin - [0..26]; col - [0..26]
};
