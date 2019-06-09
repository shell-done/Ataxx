#include "mainmenu.h"

const int MainMenu::topTextY = 290;

MainMenu::MainMenu(int width, int height, GameCore* game, QObject* parent) : Menu(width, height, game, "menus/main_menu.png", parent) {
	m_background = nullptr;

	placeButtons();
}

void MainMenu::placeButtons() {
	QVector<QString> menuText;
	menuText << "local" << "online" << "textures" << "options" << "quit";

	for(int i=0; i<5; i++) {
		m_buttons[i] = new GraphicsButton(m_game, "menus/selector.png", "graphic:menu:main:" + menuText[i], 50);
		addItem(m_buttons[i]);
		hCenter(m_buttons[i], topTextY + 75*i);
	}

	m_buttons[1]->setDisabled(true);

	connect(m_buttons[0], SIGNAL(clicked()), this, SLOT(localGame()));
	connect(m_buttons[2], SIGNAL(clicked()), this, SLOT(texturesPacks()));
	connect(m_buttons[3], SIGNAL(clicked()), this, SLOT(options()));
	connect(m_buttons[4], SIGNAL(clicked()), this, SLOT(quit()));
}

void MainMenu::update() {
	for(int i=0; i<5; i++) {
		m_buttons[i]->update();
		hCenter(m_buttons[i], topTextY + 75*i);
	}

	Menu::update();
}


void MainMenu::localGame() {
	m_game->setGameStatus(LOCAL_OPTIONS);
}

void MainMenu::texturesPacks() {
	m_game->setGameStatus(ON_TEXTURES_MENU);
}

void MainMenu::options() {
	m_game->setGameStatus(ON_OPTIONS_MENU);
}

void MainMenu::quit() {
	m_game->setGameStatus(QUIT);
}
