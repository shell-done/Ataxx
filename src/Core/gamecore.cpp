#include "gamecore.h"

using namespace std;

GameCore::GameCore(const QMap<QString, QString>& arguments, QObject *parent) : QObject(parent) {
	m_translator = new Translator(DIR_LANGUAGES);
	m_textures = nullptr;

	if(arguments.value("mode", "graphic") == "mixed")
		m_displayMode = MIXED;
	else if(arguments.value("mode", "graphic") == "graphic")
		m_displayMode = GRAPHIC;
	else
		m_displayMode = CONSOLE;

	if(m_displayMode == GRAPHIC || m_displayMode == MIXED) {
		m_textures = new Textures(DIR_TEXTURES);
		connect(m_textures, SIGNAL(updateTextures()), this, SLOT(texturesUpdated()));
	}

	m_gameStatus = ON_MAIN_MENU;
	m_volume = 75;

	srand(static_cast<unsigned int>(time(nullptr)));
}

void GameCore::update() {
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

Translator* GameCore::tr() const {
	return m_translator;
}

Textures* GameCore::textures() const {
	return m_textures;
}

e_displayMode GameCore::displayMode() const {
	return m_displayMode;
}

e_gameStatus GameCore::gameStatus() const {
	int status = m_gameStatus;
	status = (status/100)*100;

	return static_cast<e_gameStatus>(status);
}

e_gameStatus GameCore::gameSubStatus() const {
	int status = m_gameStatus;
	status = (status/10)*10;

	return static_cast<e_gameStatus>(status);
}

e_gameStatus GameCore::gameSubSubStatus() const {
	return m_gameStatus;
}

void GameCore::setGameStatus(const e_gameStatus& status) {
	m_gameStatus = status;

	if(m_displayMode != CONSOLE)
		update();
}

void GameCore::addPlayer(int p) {
	int totPlayers = m_board.playersNumber();

	if(p == 1 && totPlayers < 4) totPlayers++;
	else if(p == -1 && totPlayers > 2) totPlayers--;

	QVector<char> players;
	for(int i = 0; i < totPlayers; i++)
		players << static_cast<char>('A' + i);

	m_board.setPlayersList(players);
}

void GameCore::addSize(int s) {
	if(m_board.width() + s >= 5 && m_board.width() + s <= 12) {
		m_board.setWidth(m_board.width() + s);
		m_board.setHeigh(m_board.height() + s);
	}
}

void GameCore::changeWall() {
	m_board.setWalls(!m_board.walls());
}

int GameCore::volume() {
	return m_volume;
}

void GameCore::addVolume(int v) {
	if(m_volume + v >= 0 && m_volume + v <= 100)
		m_volume += v;

	emit volumeChanged(m_volume);
}

Board* GameCore::board() {
	return &m_board;
}

void GameCore::texturesUpdated() {
	emit updateWindow();
}
