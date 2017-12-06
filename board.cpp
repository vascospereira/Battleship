#include "board.h"
#include "utils.h"

using namespace std;


Board::Board(): num_of_rows(STANDARD_BOARD), num_of_columns(STANDARD_BOARD)
{
	vector<int> rows;
	for (uint16_t row = 0; row < this->num_of_rows; row++) {
		for (uint16_t column = 0; column < this->num_of_columns; column++) {
			rows.push_back(-1);
		}
		board.push_back(rows);
	}
}

Board::Board(const string &filename) 
{
	string row, attribute, num_lines_str, num_columns_str;
	char symbol, orientation;
	int size, color;
	PositionChar pc;

	ifstream in_file(filename.c_str());

	if (!in_file) {
		cout << "File " << filename << " does not exist!" << endl;
		cin.get(); // Stops screen before exit
		exit(1);
	}
	// Reads the first row's file
	getline(in_file, row);
	// Reads each char of row variable to numLineStr except the 'x'
	unsigned i = 0;
	while (row[i] != 'x') {
		num_lines_str.push_back(row[i]);
		i++;
	}
	i++;
	while (i < row.size()) {
		num_columns_str.push_back(row[i]);
		i++;
	}

	num_of_rows = stoi(num_lines_str);
	num_of_columns = stoi(num_columns_str);

	// Fill the board
	vector<int> rows;
	for (unsigned row = 0; row < num_of_rows; row++) {
		for (unsigned column = 0; column < num_of_columns; column++) {
			rows.push_back(-1);
		}
		board.push_back(rows);
	}

	while (!in_file.eof()) {

		getline(in_file, row);
		uint16_t i = 0;
		uint16_t index = 0;

		while (index < row.size()) {
			if (row[index] == ' ') {
				switch (i) {
				case 0:
					symbol = attribute[0];
					attribute = "";
					break;
				case 1:
					size = stoi(attribute);
					attribute = "";
					break;
				case 2:
					pc.row = attribute[0];
					pc.column = attribute[1];
					attribute = "";
					break;
				case 3:
					orientation = attribute[0];
					attribute = "";
					break;
				}
				i++;
			}
			else {
				attribute.push_back(row[index]);
			}
			index++;
		}
		color = stoi(attribute);
		// Lets build our ship.
		Ship ship(symbol, pc, orientation, size, color);

		if (!launch_ship(ship)) {
			cout << "Ship Not Launched!" << endl;
			cin.get();
			exit(1);
		}

		attribute = "";
	}

	in_file.close();
}

bool Board::launch_ship(Ship &ship) {

	if (!can_launch_ship(ship.getPosition().col, ship.getPosition().lin, ship.getOrientation(), ship.getSize())) {
		return false;
	}
	
	ships.push_back(ship);

	if (ship.getOrientation() == 'H') {
		// Saves ship size in file defined position 
		for (uint16_t j = 0, ship_size = ship.getSize(); j < ship_size; j++) {
			board.at(ship.getPosition().lin).at(ship.getPosition().col + j) = ships.size() - 1;
		}
	}
	else {
		for (uint16_t j = 0, ship_size = ship.getSize(); j < ship_size; j++) {
			board.at(ship.getPosition().lin + j).at(ship.getPosition().col) = ships.size() - 1;
		}
	}
	// Yes, we launch the ship at sea!
	return true; 
}

bool Board::can_launch_ship(int column, int row, char direction, int size)
{
	if (direction == 'H') {
		for (uint16_t j = 0; j < size; j++) {
			if ((column + size) > num_of_columns)
				return false;
			else if (board.at(row).at(column + j) != -1)
				return false;
		}
	}
	else {
		for (uint16_t j = 0; j < size; j++) {
			if ((row + size) > num_of_rows)
				return false;
			else if (board.at(row + j).at(column) != -1)
				return false;
		}
	}
	
	return true;
}

void Board::move_ships()
{
	//srand(time(NULL));
	int direction, rotate;
	for (unsigned i = 0; i < ships.size(); i++){
		bool launched = false;
		// 40% prob. of movement
		direction = rand() % 10;
		rotate = rand() % 1;
		switch (direction) {
		case NORTH:
			ships.at(i).move('N', rotate);
			break;
		case SOUTH:
			ships.at(i).move('S', rotate);
			break;
		case WEST:
			ships.at(i).move('W', rotate);
			break;
		case EAST:
			ships.at(i).move('E', rotate);
			break;
		default:
			break;
		}
	}
}


bool Board::attack(const Bomb &bomb)
{

	unsigned column = bomb.getTargetPosition().column - 97;
	unsigned row = bomb.getTargetPosition().row - 65;

	// Return value that represents the ship index in vector ships.
	int index = board.at(row).at(column); 

	// If bomb dives in water
	if (index == -1) {
		return false;
	}
		
	if (ships.at(index).getOrientation() == 'H'){
		ships.at(index).attack(column - ships.at(index).getPosition().col);
	}
	else{
		ships.at(index).attack(row - ships.at(index).getPosition().lin);
	}
	return true;

}

uint16_t Board::ships_destroyed() const
{
	uint16_t ships_destroyed = 0;
	for (uint16_t i = 0; i < ships.size(); i++) {
		if (ships.at(i).isdestroyed()) {
			ships_destroyed++;
		}
	}
	return ships_destroyed;
}

/* Creates a file with new board */
void Board::create_board_file(string &fileName)
{
	stringstream ss;
	ss << itos(num_of_columns) << " x " << itos(num_of_rows);

	ofstream out_file;
	out_file.open(fileName.c_str());
	out_file << ss.str();
	for (uint16_t i = 0; i < ships.size(); i++){
		out_file << "\n";
		out_file << ships.at(i).getSymbol() << " " << ships.at(i).getSize() << " " << (char)ships.at(i).getPosition().lin + 65 << (char)ships.at(i).getPosition().col + 97 << " ";
		if (ships.at(i).getOrientation() == 'H')
			out_file << "H";
		else out_file << "V";
		out_file << " " << itos(ships.at(i).getColor());
	}
	out_file.close();
}

void Board::display() const {

	/* Prints uppercase letters */
	for (auto i = 0; i < num_of_columns; i++) {
		gotoxy(i * 2 + 2, 0);
		setcolor(WHITE, BLACK);
		cout << (char)(97 + i); //ASCII a... codes
	}

	for (auto i = 0; i < num_of_rows; i++) {
		gotoxy(0, i + 1);
		setcolor(WHITE, BLACK);
		cout << (char)(65 + i);
	}

	/* Prints board */
	for (auto i = 0; i < num_of_rows; i++) {
		for (auto j = 0; j < num_of_columns; j++) {
			gotoxy(j * 2 + 1, i + 1);
			if (board.at(i).at(j) == -1) {
				setcolor(LIGHTBLUE, LIGHTGRAY);
				cout << " . ";
			}
			else {
				setcolor(ships.at(board.at(i).at(j)).getColor(), LIGHTGRAY);

				if (ships.at(board.at(i).at(j)).getOrientation() == 'H') {
					unsigned pos = j - ships.at(board.at(i).at(j)).getPosition().col;
					cout << " " << ships.at(board.at(i).at(j)).getStatus()[pos] << " ";
				}
				else {
					unsigned pos = i - ships.at(board.at(i).at(j)).getPosition().lin;
					cout << " " << ships.at(board.at(i).at(j)).getStatus()[pos] << " ";
				}
			}
		}
	}


	setcolor(WHITE, BLACK);
	cout << endl << endl;

}


void Board::show() const 
{
	cout << "Number of Rows: " << num_of_rows << " Number of Columns: " << num_of_columns << endl;
	cout << "Ships: " << endl;
	for (unsigned i = 0; i < ships.size(); i++){
		cout << "Ship " << i << ":" << endl;
		ships[i].show();
		cout << endl;
	}
	cout << endl;
}
