#include "player.h"
#include "utils.h"
#include <algorithm>

/* Program utils functions */
string itos(int32_t integer)
{
	string ret;

	while (integer > 0){
		ret.push_back((integer % 10) + 48); // ASCII -> Inteiro
		integer /= 10;
	}

	reverse(ret.begin(), ret.end());

	return ret;
}

bool fileExists(string filename)
{
	ifstream fin(filename.c_str());
	if (fin.is_open()){
		fin.close();
		return true;
	}
	else {
		return false;
	}
		
}

void showLogicBoard(Board b)
{
	vector<vector<int> > board = b.get_board();
	//vector<vector<int> > arr = { { 1,-2 },{ 3,4,-9,0 },{6,-7,8} };
	/*
	for_each(begin(arr), end(arr), [&](const std::vector<int>& col)
	{
		for_each(begin(col), end(col), [&](int x)
		{
			cout << setw(2) << x << " ";
		});
		cout << endl;
	});
	*/
	
	for (uint16_t i = 0; i < board.size(); i++) {
		for (uint16_t j = 0; j < board.at(0).size(); j++) {
			cout << setw(2) << board.at(i).at(j) << " ";
		}
		cout << endl;
	}
	
}

//cleans map 
Scores::Scores()
{
	scores.clear();
}

//Loads scores from file
Scores::Scores(string filename): fileScores(filename)
{
	if (fileExists(fileScores)) {
		loadScores(fileScores);
	}
	else {
		scores.clear();
	}
}

//Saves scores into file scores.txt
Scores::~Scores()
{
	saveScores(fileScores);
}

//Add scores to map
void Scores::addScores(unsigned score, std::string name)
{
	scores[score] = name;
}

//Shows map scores in ascendent order
void Scores::printScores(ostream &out) const
{
	const unsigned adjust = 5;
	MapIterator current = scores.begin();
	MapIterator stop = scores.end();
	cout << endl;
	out << "\nGame scores: " << endl;
	while (current != stop){
		out.width(adjust);
		out << right << current->first << " - " << current->second << '\n';
		++current;
	}
}

/*Overload << operator for class Scores*/
ostream & operator<< (ostream &out, Scores &score)
{
	const unsigned adjust = 5;
	map<unsigned, string>::const_iterator current = score.scores.begin();
	map<unsigned, string>::const_iterator stop = score.scores.end();
	out << "\nGame scores: " << endl;
	while (current != stop){
		out.width(adjust);
		out << right << current->first << " - " << current->second << '\n';
		++current;
	}
	return out;
}

//Save scores and player name into file
void Scores::saveScores(string fileScores)
{
	ofstream fout;
	MapIterator current = scores.begin();
	MapIterator stop = scores.end();

	fout.open(fileScores.c_str());
	if (fout.fail()) {
		cout << "Output file opening failed.\n";
		exit(1);
	}

	while (current != stop) {
		fout << current->first << " - " << current->second << '\n';
		++current;
	}
	fout.close();
}

//Loads scores and player name from file
void Scores::loadScores(string fileScores)
{
	ifstream fin;
	unsigned score;
	string name;
	char dash;
	scores.clear();

	fin.open(fileScores.c_str());
	if (fin.fail()){
		cout << "Input file fail to open.\n";
		cin.get();
		exit(1);
	}

	while (!fin.eof()){
		fin >> score >> dash >> name;
		addScores(score, name);
	}
	fin.close();
}

uint8_t colorInterpreter(const string color)
{
	if (color == "BLACK")
		return BLACK;
	else if (color == "BLUE")
		return BLUE;
	else if (color == "GREEN")
		return GREEN;
	else if (color == "CYAN")
		return CYAN;
	else if (color == "RED")
		return RED;
	else if (color == "MAGENTA")
		return MAGENTA;
	else if (color == "BROWN")
		return BROWN;
	else if (color == "LIGHTGRAY")
		return LIGHTGRAY;
	else if (color == "DARKGRAY")
		return DARKGRAY;
	else if (color == "LIGHTBLUE")
		return LIGHTBLUE;
	else if (color == "LIGHTGREEN")
		return LIGHTGREEN;
	else if (color == "LIGHTCYAN")
		return LIGHTCYAN;
	else if (color == "LIGHTRED")
		return LIGHTRED;
	else if (color == "LIGHTMAGENTA")
		return LIGHTMAGENTA;
	else if (color == "YELLOW")
		return YELLOW;
	else if (color == "WHITE")
		return WHITE;
	return -1;
}

void clrscr(void)
{
	// upper left corner
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	DWORD dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, coordScreen);
}

//==========================================================================================
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//==========================================================================================
void setcolor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

//==========================================================================================
void setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == BLACK) {
		SetConsoleTextAttribute(hCon, color);
	}
	else {
		SetConsoleTextAttribute(hCon, color | background_color * 16 + color);
	}
}
