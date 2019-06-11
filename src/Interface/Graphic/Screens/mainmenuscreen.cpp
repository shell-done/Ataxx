#include "mainmenuscreen.h"

const int MainMenuScreen::topTextY = 310;

MainMenuScreen::MainMenuScreen(int width, int height, GameCore* game, QObject* parent) : Screen(width, height, game, "menus/main_menu.png", parent) {
	placeButtons();
}

void MainMenuScreen::placeButtons() {
	QVector<QString> menuText;
	menuText << "local" << "online" << "textures" << "options" << "quit";

	//Instancies et place les boutons
	for(int i=0; i<5; i++) {
		m_buttons[i] = new GraphicsButtonItem(m_game, "menus/selector.png", "graphic:menu:main:" + menuText[i], 40);
		addItem(m_buttons[i]);
	}

	//Désactive le deuxième bouton car le mode en ligne n'est pas encore disponible
	m_buttons[1]->setDisabled(true);

	//Connecte tous les boutons
	connect(m_buttons[0], SIGNAL(clicked()), this, SLOT(localGame()));
	connect(m_buttons[2], SIGNAL(clicked()), this, SLOT(texturesPacks()));
	connect(m_buttons[3], SIGNAL(clicked()), this, SLOT(options()));
	connect(m_buttons[4], SIGNAL(clicked()), this, SLOT(quit()));

	update();
}

void MainMenuScreen::update() {
	//Met à jour chaque item
	for(int i=0; i<5; i++) {
		m_buttons[i]->update();
		hCenter(m_buttons[i], topTextY + 65*i);
	}

	Screen::update();
}


void MainMenuScreen::localGame() {
	m_game->setGameStatus(LOCAL_OPTIONS);
}

void MainMenuScreen::texturesPacks() {
	m_game->setGameStatus(ON_TEXTURES_MENU);
}

void MainMenuScreen::options() {
	m_game->setGameStatus(ON_OPTIONS_MENU);
}

void MainMenuScreen::quit() {
	m_game->setGameStatus(QUIT);
}
