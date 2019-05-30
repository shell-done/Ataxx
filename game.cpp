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

	if(m_displayMode == GRAPHIC || m_displayMode == MIXED) {
		m_textures = new Textures(DIR_TEXTURES);
		connect(m_textures, SIGNAL(updateTextures()), this, SLOT(texturesUpdated()));
	}

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

void Game::addPlayer(int p) {
	int totPlayers = m_board.playersNumber();

	if(p == 1 && totPlayers < 4) totPlayers++;
	else if(p == -1 && totPlayers > 2) totPlayers--;

	QVector<char> players;
	for(int i = 0; i < totPlayers; i++)
		players << static_cast<char>('A' + i);

	m_board.setPlayersList(players);
}

void Game::addSize(int s) {
	if(m_board.width() + s >= 5 && m_board.width() + s <= 15) {
		m_board.setWidth(m_board.width() + s);
		m_board.setHeigh(m_board.height() + s);
	}
}

void Game::changeWall() {
	m_board.setWalls(!m_board.walls());
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

void Game::texturesUpdated() {
	emit updateWindow();
}
