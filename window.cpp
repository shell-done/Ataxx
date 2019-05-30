#include "window.h"

const int Window::m_width = 1280;
const int Window::m_height = 720;

Window::Window(Game* game) : QGraphicsView(), m_game(game) {
	m_mainMenu = new MainMenu(m_width, m_height, game, this);
	m_partyOptionsMenu = new PartyOptionsMenu(m_width, m_height, game, this);
	m_characterSelectionMenu = new CharacterSelectionMenu(m_width, m_height, game, this);
	m_texturesMenu = new TexturesMenu(m_width, m_height, game, this);
	m_optionsMenu = new OptionsMenu(m_width, m_height, game, this);

	setFixedSize(m_width + 2, m_height + 2);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setMouseTracking(true);
	setScene(m_mainMenu);

	connect(m_game, SIGNAL(updateWindow()), this, SLOT(gameUpdate()));
}

void Window::gameUpdate() {
	if(m_game->gameStatus() == QUIT)
		close();

	switch(m_game->gameSubSubStatus()) {
	case QUIT:
		close();
		break;

	case ON_MAIN_MENU:
		setScene(m_mainMenu);
		m_mainMenu->update();
		break;

	case LOCAL_OPTIONS:
		setScene(m_partyOptionsMenu);
		m_partyOptionsMenu->update();
		break;

	case LOCAL_CHARACTER_SELECTION:
		setScene(m_characterSelectionMenu);
		m_characterSelectionMenu->update();
		break;

	case ON_TEXTURES_MENU:
		setScene(m_texturesMenu);
		m_texturesMenu->update();
		break;

	case ON_OPTIONS_MENU:
		setScene(m_optionsMenu);
		m_optionsMenu->update();
		break;

	default:
		break;
	}
}
