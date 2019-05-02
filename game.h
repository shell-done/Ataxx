#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "core.h"
#include "translator.h"
#include "textures.h"
#include "board.h"

class Game : public QObject {
	Q_OBJECT

public:
	Game(const QMap<QString, QString>& arguments, QObject *parent = nullptr);
	void start();
	void update();

	Translator* tr() const;
	Textures* textures() const;
	e_displayMode displayMode() const;

	e_gameStatus gameStatus() const;
	e_gameStatus gameSubStatus() const;
	e_gameStatus gameSubSubStatus() const;
	void setGameStatus(const e_gameStatus& gameStatus);

	Board* board();

private:
	Translator* m_translator;
	Textures* m_textures;
	e_displayMode m_displayMode;

	e_gameStatus m_gameStatus;

	Board m_board;

signals:
	void updateConsole();
	void updateWindow();
};

#endif // GAME_H
