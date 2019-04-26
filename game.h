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
	e_optionsStatus optionStatus;

	Translator translator;

	int getUserInput();

	void displayMenu();
	void changeMenu(int userInput = -1);

	void displayOptions();
	void changeOptions(int userInput = -1);

};

#endif // GAME_H
