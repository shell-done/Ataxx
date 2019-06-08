#ifndef BOARD_H
#define BOARD_H

#include <QPoint>
#include <QVector>
#include "core.h"

class Board {
public:
	Board();

	void generate();
	void placePawns();
	bool exists();
	void destroy();

	char** boxes() const;

	int width();
	void setWidth(int width);
	int height();
	void setHeigh(int height);
	QVector<char> playersList();
	void setPlayersList(QVector<char> players);
	void setPlayerChar(int playerIdx, char c);
	int playersNumber();
	bool walls();
	void setWalls(bool);

	int round();
	char currentPlayer();

	bool onGrid(const QPoint& point);
	char at(const QPoint& point);
	void setCharacter(const QPoint& point, char character);
	bool boxBelongByCurrentPlayer(const QPoint& point);

	QPair<QPoint, QPoint> strToPoints(const QStringList& coordinates);
	bool moveAllowed(const QPoint& origin, const QPoint& dest);
	QVector<QPoint> movesAllowed(const QPoint& src);
	void playMove(const QPoint& origin, const QPoint& dest);

	QMap<char, int> countPawns();
	bool currentPlayerCanPlay();
	char checkVictory();

	static const char emptyBoxCharacter;
	static const char P1Character;
	static const char P2Character;

private:
	int m_width;
	int m_height;
	bool m_createWalls;

	int m_round;
	char m_currentPlayer;

	QVector<char> m_playersList;

	char** m_boxes;
};

#endif // BOARD_H
