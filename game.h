#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "core.h"
#include "translator.h"

class Game : public QObject {
	Q_OBJECT

public:
	Game(QObject *parent = nullptr);
	virtual ~Game();

	void play();

private:
	e_gameStatus gameStatus;
	Translator translator;

	void displayMenu();
};

#endif // GAME_H
