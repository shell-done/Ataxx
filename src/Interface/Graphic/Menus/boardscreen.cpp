#include "boardscreen.h"

BoardScreen::BoardScreen(int width, int height, GameCore* game, QObject* parent) : Menu(width, height, game, parent) {
	m_background = addPixmap(m_textures->loadPixmap("menus/game_background.png"));
	m_graphicsBoardItem = nullptr;
}

void BoardScreen::generateBoard() {
	if(m_graphicsBoardItem) {
		removeItem(m_graphicsBoardItem);
		delete m_graphicsBoardItem;

		m_graphicsBoardItem = nullptr;
	}

	m_graphicsBoardItem = new GraphicsBoardItem(m_game);
	addItem(m_graphicsBoardItem);

	center(m_graphicsBoardItem);
}

void BoardScreen::update() {
	if(m_graphicsBoardItem)
		m_graphicsBoardItem->updateBoard();
}
