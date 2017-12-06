#include "bomb.h"

using namespace std;

Bomb::Bomb(PositionChar targetPosition): targetRow(targetPosition.row), targetColumn(targetPosition.column) {}

PositionChar Bomb::getTargetPosition() const{
	PositionChar pc;
	pc.row = targetRow;
	pc.column = targetColumn;
	return pc;
}

void Bomb::show() const{
	cout << "Row: " << targetRow << " Column: " << targetColumn << endl;
}
