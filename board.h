#ifndef BOARD_H
#define BOARD_H

#include <QPoint>
#include <QVector>
#include "core.h"

class Board {
public:
	Board();

	void generate();
	bool exists();

	char** boxes() const;

	int width();
	void setWidth(int width);

	int height();
	void setHeigh(int height);

	int round();
	char currentPlayer();

	bool onGrid(const QPoint& point);
	char at(const QPoint& point);
	void setCharacter(const QPoint& point, char character);
	bool moveAllowed(const QPoint& origin, const QPoint& dest);
	void playMove(const QPoint& origin, const QPoint& dest);

	char checkWinner();

private:
	static const char emptyBoxCharacter;
	static const char P1Character;
	static const char P2Character;

	int m_width;
	int m_height;

	int m_round;
	char m_currentPlayer;

	QVector<char> m_playersList;

	char** m_boxes;
};

#endif // BOARD_H
