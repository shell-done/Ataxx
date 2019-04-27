#ifndef CORE_H
#define CORE_H

#include <QCoreApplication>
#include <QString>
#include <iostream>

#define DIR_LANGUAGES QString("./lang")

typedef enum e_gameStatus {
	QUIT, ON_MAIN_MENU, ON_LOCAL_MENU, ON_TEXTURES_MENU, ON_OPTIONS_MENU, IG_LOCAL, IG_ONLINE
} e_gameStatus;

typedef enum e_localPartyStatus {
	LOCAL_MENU, LOCAL_PARTY_SETTINGS, LOCAL_PARTY_MAP, LOCAL_PARTY_P1, LOCAL_PARTY_P2
} e_localPartyStatus;

typedef enum e_optionsStatus {
	OPTIONS_MENU, SET_LANGUAGE
} e_optionsStatus;

#endif // CORE_H
