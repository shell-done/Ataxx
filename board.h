#ifndef BOARD_H
#define BOARD_H

#include "core.h"

class Board {
public:
	Board();

	void generate();
	bool exists();

	int width();
	void setWidth(int width);

	int height();
	void setHeigh(int height);

private:
	static const char emptyBoxCharacter;
	static const char P1Character;
	static const char P2Character;

	int m_width;
	int m_height;

	char** m_boxes;
};

#endif // BOARD_H
