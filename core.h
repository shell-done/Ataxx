#ifndef CORE_H
#define CORE_H

#include <QCoreApplication>
#include <QString>
#include <iostream>
#include <cmath>

#include <QDebug>

#define DIR_LANGUAGES QString("./lang/")
#define DIR_TEXTURES QString("./textures packs/")

typedef enum e_displayMode {
	CONSOLE, GRAPHIC, MIXED
} e_displayMode;

typedef enum e_gameStatus {
	QUIT = 000,
	ON_MAIN_MENU = 100,
	LOCAL_PARTY = 200,
		LOCAL_IN_GAME = 210,
	IG_ONLINE = 300,
	ON_OPTIONS_MENU = 400,
		ON_LANGUAGES_MENU = 410
} e_gameStatus;

QMap<QString, QString> readArguments(int argc, char** argv, QMap<QString, QString> defaultValues = QMap<QString, QString>());

#endif // CORE_H
