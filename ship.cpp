#include "ship.h"

using namespace std;


/* Color coversion to strings */
string colorInterpreter(const int color){
	if (color == BLACK)
		return "Black";
	else if (color == BLUE)
		return "Blue";
	else if (color == GREEN)
		return "Green";
	else if (color == CYAN)
		return "Cyan";
	else if (color == RED)
		return "Red";
	else if (color == MAGENTA)
		return "Magenta";
	else if (color == BROWN)
		return "Brown";
	else if (color == LIGHTGRAY)
		return "Light Gray";
	else if (color == DARKGRAY)
		return "Dark Gray";
	else if (color == LIGHTBLUE)
		return "Light Blue";
	else if (color == LIGHTGREEN)
		return "Light Green";
	else if (color == LIGHTCYAN)
		return "Light Cyan";
	else if (color == LIGHTRED)
		return "Light Red";
	else if (color == LIGHTMAGENTA)
		return "Light Magenta";
	else if (color == YELLOW)
		return "Yellow";
	else if (color == WHITE)
		return "White";
	return "";
}

Ship::Ship(char symbol, PositionChar position, char orientation, unsigned size, unsigned color):
	symbol(symbol),
	orientation(orientation),
	size(size),
	color(color)
{
	// Set start ship position coordinates
	PositionInt pi;
	pi.col = position.column - 'a';
	pi.lin = position.row - 'A';

	this->position = pi;

	for (auto i = 0; i < size; i++) {
		status.push_back(symbol);
	}
}

void Ship::move(char direction, bool rotate) {
	switch (direction){
	case 'N':
		position.lin--;
		break;
	case 'S':
		position.lin++;
		break;
	case 'W':
		position.col--;
		break;
	case 'E':
		position.col++;
		break;
	}
}

bool Ship::attack(size_t ship_part) {
	if (ship_part >= status.size())
		return false;
	status[ship_part] = tolower(status[ship_part]);
	return true;
}

bool Ship::isdestroyed() const 
{
	unsigned destroyed_parts = 0;
	for (auto i = 0; i < status.size(); i++) {
		if (islower(status[i])) {
			destroyed_parts++;
			//cout << status[i] << endl;
		}
	}
	//system("PAUSE");
	if (destroyed_parts == status.size())
		return true;
	else 
		return false;
}

void Ship::show() const{
	cout << "Symbol: " << symbol << "\nRow (1st part): " << position.lin << 
		"\nColumn (1st part): " << position.col << endl << 
		"\nOrientation: " << orientation << "\nSize: " << size << "\nColor: " << 
		colorInterpreter(color) << "\nStatus: " << status << endl;
}
