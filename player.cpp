#include "player.h"
#include "utils.h"
#include "board.h"

using namespace std;

Player::Player(string playerName, Board &board): name(playerName), board(board){}

Player::Player(string playerName, string boardFilename): name(playerName), board(Board(boardFilename)){}

void Player::show_board() const
{
	clrscr();
	board.display();
}

Bomb Player::get_bomb() const
{
	//srand(time(NULL));

	// Do input control
	char row, column;
	do
	{
		cout << "Target coordinates (row, column) ? ";
		cin >> row >> column;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		row = toupper(row);
		column = tolower(column);
	} while (row < 'A' || row > 'J' || column < 'a' || column > 'j');


	// Create some defect bomb degree (60%)
	int aim = rand() % 10;
	// Make sure defect bomb aim to the 'sea'
	if ((aim == 0 && row == 'A') || (aim == 1 && row == 'J') || (column == 'a' && aim == 2 ) || (column == 'j' && aim == 3))
		aim = 5;

	switch (aim) {
	case NORTH:
		row--;
		break;
	case SOUTH:
		row++;
		break;
	case WEST:
		column--;
		break;
	case EAST:
		column++;
		break;
	default:
		break;
	}
	

	PositionChar pc;
	pc.row = row;
	pc.column = column;

	return Bomb(pc);
}

void Player::board_attacked(const Bomb &bomb)
{
	//board.moveShips();
	board.attack(bomb);
}

void Player::show() const 
{
	cout << "Name: " << name << endl;
	board.show();
}
