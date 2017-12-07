#include "player.h"
#include "utils.h"

using namespace std;

int main(){

	setcolor(WHITE, BLACK);

	Board b_1("C:\\Users\\Anonymous\\Desktop\\Battleship\\board.txt");
	Board b_2("C:\\Users\\Anonymous\\Desktop\\Battleship\\vessel.txt");
	const uint16_t number_of_ships = b_1.get_ships().size();
	PositionChar pos;

	Player player_1("Cabral", b_1), 
		player_2("Gama", b_2);

	while (1) {

		//PLAYER 1
		player_1.show_board();
		cout << "Player: " << player_1.get_name() << endl;
		cout << "Destroyed Ships: " << player_1.ships_destroyed() << endl;
		if (number_of_ships == player_1.ships_destroyed()) {
			cout << "You Lost! Try again." << endl;
			break;
		}
		Bomb bomb = player_1.get_bomb();
		player_2.board_attacked(bomb);

		// PLAYER 2
		player_2.show_board();
		cout << "Player: " << player_2.get_name() << endl;
		cout << "Destroyed Ships: " << player_2.ships_destroyed() << endl;
		if (number_of_ships == player_2.ships_destroyed()) {
			cout << "You Lost! Try again." << endl;
			break;
		}
		bomb = player_2.get_bomb();
		player_1.board_attacked(bomb);

	}

	//showLogicBoard(b_1);

	//time_t timeP1, time2P1, timeP2, time2P2;
	//time_t elapsedTimeP1 = 0, elapsedTimeP2 = 0;
	//srand((unsigned)time(NULL));

	//Scores PlayerScores("C:\\Users\\Anonymous\\Desktop\\bship\\scores.txt");
	//string player1Name = p1.getName();
	//string player2Name = p2.getName();
	//PlayerScores.addScores(elapsedTimeP1, player1Name);
	//PlayerScores.addScores(elapsedTimeP2, player2Name);
	//PlayerScores.printScores(cout);
	/*Overload operator << with Scores class to extract info over map container*/
	//cout << PlayerScores;

	system("PAUSE");
	return 0;
}