#include "boardscreen.h"

BoardScreen::BoardScreen(int width, int height, GameCore* game, QObject* parent) : Menu(width, height, game, parent) {
	m_background = addPixmap(m_textures->loadPixmap("menus/game_background.png"));
	m_background->setZValue(-1);
	m_graphicsBoardItem = nullptr;

	m_buttons[0] = new GraphicsButton(game, "menus/half_selector.png", "graphic:local:game:restart", 50);
	m_buttons[1] = new GraphicsButton(game, "menus/half_selector.png", "graphic:local:game:quit", 50);
	addItem(m_buttons[0]);
	addItem(m_buttons[1]);

	connect(m_buttons[1], SIGNAL(clicked()), this, SLOT(quit()));
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
	update();
}

void BoardScreen::update() {
	if(m_graphicsBoardItem)
		m_graphicsBoardItem->updateBoard();

	for(int i=0; i<2; i++)
		m_buttons[i]->update();

	placeItems();
}

void BoardScreen::placeItems() {
	int columnWidth = static_cast<int>((width() - m_graphicsBoardItem->boundingRect().width() - 40)/2);
	int rightColumnX = static_cast<int>(m_graphicsBoardItem->x() + m_graphicsBoardItem->boundingRect().width() + 10);

	int buttonX = static_cast<int>(rightColumnX + (columnWidth - m_buttons[0]->boundingRect().width())/2);
	m_buttons[1]->setPos(buttonX, height() - m_buttons[1]->boundingRect().height() - 50);
	m_buttons[0]->setPos(buttonX, m_buttons[1]->y() - m_buttons[0]->boundingRect().height() - 30);

	m_buttons[0]->setZValue(10);
}

void BoardScreen::quit() {
	m_game->board()->destroy();
	m_game->setGameStatus(ON_MAIN_MENU);
}
