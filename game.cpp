#include "game.h"

using namespace std;

Game::Game(const QMap<QString, QString>& arguments, QObject *parent) : QObject(parent) {
	m_translator = new Translator(DIR_LANGUAGES);
	m_textures = nullptr;

	if(arguments.value("mode", "console") == "mixed")
		m_displayMode = MIXED;
	else if(arguments.value("mode", "console") == "graphic")
		m_displayMode = GRAPHIC;
	else
		m_displayMode = CONSOLE;

	if(m_displayMode == GRAPHIC || m_displayMode == MIXED)
		m_textures = new Textures(DIR_TEXTURES);

	m_gameStatus = ON_MAIN_MENU;
	m_volume = 75;
}

void Game::update() {
	switch(m_displayMode) {
	case CONSOLE:
		while(m_gameStatus != QUIT)
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

Textures* Game::textures() const {
	return m_textures;
}

e_displayMode Game::displayMode() const {
	return m_displayMode;
}

e_gameStatus Game::gameStatus() const {
	int status = m_gameStatus;
	status = (status/100)*100;

	return static_cast<e_gameStatus>(status);
}

e_gameStatus Game::gameSubStatus() const {
	int status = m_gameStatus;
	status = (status/10)*10;

	return static_cast<e_gameStatus>(status);
}

e_gameStatus Game::gameSubSubStatus() const {
	return m_gameStatus;
}

void Game::setGameStatus(const e_gameStatus& status) {
	m_gameStatus = status;

	if(m_displayMode != CONSOLE)
		update();
}

QString Game::volume() {
	return QString::number(m_volume).rightJustified(3, ' ');
}

void Game::addVolume(int v) {
	if(m_volume + v >= 0 && m_volume + v <= 100)
		m_volume += v;
}

Board* Game::board() {
	return &m_board;
}
