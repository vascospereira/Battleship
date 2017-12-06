#pragma once

#include "symbolics.h"
#include <iostream>

class Bomb {
public:
	Bomb(PositionChar targetPosition);
	PositionChar getTargetPosition() const;
	void show() const; // shows the attributes of the bomb (for debugging)
private:
	char targetRow, targetColumn;
};