#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include "game.h"

class Console : public QObject {
	Q_OBJECT

public:
	Console(Game* game, QObject *parent = nullptr);

private:
	void displayMainMenu();
	void displayOptionsMenu();

	void getUserInput();

	void mainMenuInput(int userInput);
	void optionsMenuInput(int userInput);

	Game* m_game;
	Translator* m_tr;

private slots:
	void gameUpdate();
};

#endif // CONSOLE_H
