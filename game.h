#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "core.h"
#include "translator.h"
#include "board.h"

class Game : public QObject {
	Q_OBJECT

public:
	Game(QObject *parent = nullptr);
	virtual ~Game();

	void play();

private:
	e_gameStatus gameStatus;
	e_localPartyStatus localPartyStatus;
	e_optionsStatus optionStatus;

	Translator translator;
	Board* board;

	int mapWidth;
	int mapHeight;

	int getUserInput();

	void displayMenu();
	void changeMenu(int userInput = -1);

	void displayLocal();
	void changeLocal(int userInput = -1);

	void displayOptions();
	void changeOptions(int userInput = -1);

};

#endif // GAME_H
