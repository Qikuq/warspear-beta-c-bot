#include "../Offsets/Offsets.h"
#pragma once

class Cursor {
public:
	uintptr_t address;
	short int x, y, cursorId;
	Cursor();
	void updateCursor();
	void move(int x, int y);
};