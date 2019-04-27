#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "core.h"
#include "translator.h"

class Game : public QObject {
	Q_OBJECT

public:
	Game(QObject *parent = nullptr);

	Translator* tr();

private:
	e_gameStatus m_gameStatus;
	Translator* m_translator;
};

#endif // GAME_H
