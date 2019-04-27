#ifndef CORE_H
#define CORE_H

#include <QCoreApplication>
#include <QString>
#include <iostream>

#include <QDebug>

#define DIR_LANGUAGES QString("./lang")

typedef enum e_displayMode {
	CONSOLE, GRAPHIC, MIXED
} e_displayMode;

typedef enum e_gameStatus {
	QUIT, ON_MAIN_MENU, ON_LOCAL_MENU, IG_LOCAL, IG_ONLINE, ON_OPTIONS_MENU
} e_gameStatus;

QMap<QString, QString> readArguments(int argc, char** argv, QMap<QString, QString> defaultValues = QMap<QString, QString>());

#endif // CORE_H
