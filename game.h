#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "core.h"
#include "translator.h"
#include "board.h"

class Game : public QObject {
	Q_OBJECT

public:
	Game(const QMap<QString, QString>& arguments, QObject *parent = nullptr);
	void start();
	void update();

	Translator* tr() const;
	e_displayMode displayMode() const;

	e_gameStatus gameStatus() const;
	void setGameStatus(const e_gameStatus& gameStatus);

	void mainMenuInput(int userInput);

private:
	Translator* m_translator;
	e_displayMode m_displayMode;

	e_gameStatus m_gameStatus;
	Board board;

signals:
	void updateConsole();
	void updateWindow();
};

#endif // GAME_H
