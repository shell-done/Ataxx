#include "game.h"

using namespace std;

Game::Game(const QMap<QString, QString>& arguments, QObject *parent) : QObject(parent) {
	m_translator = new Translator(DIR_LANGUAGES);

	if(arguments.value("mode", "console") == "mixed")
		m_displayMode = MIXED;
	else if(arguments.value("mode", "console") == "graphic")
		m_displayMode = GRAPHIC;
	else
		m_displayMode = CONSOLE;

	m_gameStatus = ON_MAIN_MENU;
}

void Game::update() {
	switch(m_displayMode) {
	case CONSOLE:
		updateConsole();
		break;

	case GRAPHIC:
		updateWindow();
		break;

	case MIXED:
		updateConsole();
		updateWindow();
		break;
	}
}

Translator* Game::tr() const {
	return m_translator;
}

e_displayMode Game::displayMode() const {
	return m_displayMode;
}

e_gameStatus Game::gameStatus() const {
	return m_gameStatus;
}

void Game::setGameStatus(const e_gameStatus& status) {
	if(m_gameStatus == status)
		return;

	m_gameStatus = status;
	update();
}

void Game::mainMenuInput(int userInput) {
	switch(userInput) {
	case 0:
		return;

	case 1:
		m_gameStatus = IG_LOCAL;
		break;

	case 2:
		m_gameStatus = IG_ONLINE;
		break;

	case 3:
		m_gameStatus = ON_OPTIONS_MENU;
		break;

	default:
		cout << m_translator->stdTranslate("console:global:error") << endl;
		break;
	}

	update();
}
