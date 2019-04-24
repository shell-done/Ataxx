#ifndef CORE_H
#define CORE_H

#include <QCoreApplication>
#include <QString>
#include <iostream>

#define DIR_LANGUAGES QString("./lang")

typedef enum e_gameStatus {
	QUIT = -1, ON_MENU, IN_GAME
} e_gameStatus;

#endif // CORE_H
