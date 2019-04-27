#ifndef BOARD_H
#define BOARD_H

#include "core.h"
#include <QObject>

class Board : public QObject {
	Q_OBJECT

public:
	Board(QObject *parent = nullptr);

	void create();
	bool exists() const;
	void display() const;

	QPair<int, int> getMapSize() const;
	char getP1Character() const;
	char getP2Character() const;

private:
	static const int defaultMapSize;
	static const char defaultEmptyCharacter;
	static const char defaultP1Character;
	static const char defaultP2Character;

	int width;
	int height;

	char p1Character;
	char p2Character;

	char** boxes;
};

#endif // BOARD_H
