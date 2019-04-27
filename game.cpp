#include "game.h"

using namespace std;

Game::Game(QObject *parent) : QObject(parent) {
	m_translator = new Translator(DIR_LANGUAGES);
	m_gameStatus = ON_MAIN_MENU;
}

Translator* Game::tr() {
	return m_translator;
}
