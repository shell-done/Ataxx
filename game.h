#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "core.h"

class Game : public QObject {
	Q_OBJECT

public:
	Game(QObject *parent = nullptr);
	virtual ~Game();

	void play();

private:
	e_gameStatus gameStatus;

	void displayMenu();
};

#endif // GAME_H
