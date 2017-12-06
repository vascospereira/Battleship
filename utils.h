#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <map>
#include <windows.h>
#include "symbolics.h"

using namespace std;

/* Util Functions */

/*Int to String*/
string itos(int32_t integer);

/* Converte a nomenculatura de cor dos ficheiros para a da API do Windows */
uint8_t colorInterpreter(const string color);

void clrscr(void);

// Position the cursor at column 'x', line 'y'
// The coodinates of upper left corner of the screen are (x,y)=(0,0)
void gotoxy(int x, int y);

// Set text color
void setcolor(unsigned int color);

// Set text color & background
void setcolor(unsigned int color, unsigned int background_color);

// Tests if a file exists
// 'filename' - file whose existence is being tested
bool fileExists(string filename);

/* Shows internal board representation */
void showLogicBoard(const Board b);


class Scores {
	friend ostream &operator<< (ostream &out, Scores &score);
public:
	Scores();
	Scores(string fileScores);
	~Scores();
	void addScores(unsigned score, string name);
	void saveScores(string fileScores);
	void loadScores(string fileScores);
	void printScores(ostream &out) const;
private:
	const string fileScores;
	map<unsigned, string> scores;
	typedef map<unsigned, string>::const_iterator MapIterator;
};
