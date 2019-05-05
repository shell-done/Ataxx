#include "mainmenu.h"

MainMenu::MainMenu(int width, int height, Game* game, QObject* parent) : QGraphicsScene(parent), m_game(game) {
	setSceneRect(0, 0, width, height);

	m_menuIdx = 0;
	m_textures = m_game->textures();
	m_tr = m_game->tr();

	m_background = nullptr;
	m_selector = nullptr;
	for(int i=0; i<5; i++)
		m_texts[i] = nullptr;

	updateTextures();
}

void MainMenu::updateTextures() {
	if(m_background) {
		m_background->setPixmap(m_textures->loadPixmap("menus/main_menu.png"));
		m_selector->setPixmap(m_textures->loadPixmap("icons/selector.png"));
	} else {
		m_background = addPixmap(m_textures->loadPixmap("menus/main_menu.png"));
		m_selector = addPixmap(m_textures->loadPixmap("icons/selector.png"));
	}
	m_selector->setPos(363, 307);

	updateText();
}

void MainMenu::updateText() {
	QVector<QString> menuText;
	menuText << "local" << "online" << "textures" << "options" << "quit";

	int x = 438, y = 289;

	for(int i=0; i<5; i++) {
		if(m_texts[i])
			m_texts[i]->setPlainText(m_tr->qTranslate("graphic:menu:main:" + menuText[i], m_textures->useAccents()));
		else
			m_texts[i] = addText(m_tr->qTranslate("graphic:menu:main:" + menuText[i], m_textures->useAccents()));

		m_texts[i]->setFont(m_textures->loadFont(50));
		m_texts[i]->setDefaultTextColor(m_textures->primaryColor());
		m_texts[i]->setPos(x, y + 75*i);
	}
}

int MainMenu::mouseHoverText(const QPoint &mousePos) {
	int hovered = -1;

	QRect rect(378, 290, 500, 75);
	for(int i=0; i<5; i++) {
		if(rect.contains(mousePos))
			hovered = i;

		rect.translate(0, 75);
	}

	return hovered;
}

void MainMenu::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	int hovered = mouseHoverText(event->scenePos().toPoint());
	if(hovered != -1)
		m_menuIdx = hovered;

	m_selector->setPos(363, 307 + m_menuIdx*75);
}
