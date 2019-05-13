#include "mainmenu.h"

const int MainMenu::topTextY = 290;

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
	updateText();
}

void MainMenu::updateTextures() {
	if(m_background) {
		m_background->setPixmap(m_textures->loadPixmap("menus/main_menu.png"));
		m_selector->setPixmap(m_textures->loadPixmap("menus/selector.png"));
	} else {
		m_background = addPixmap(m_textures->loadPixmap("menus/main_menu.png"));
		m_selector = addPixmap(m_textures->loadPixmap("menus/selector.png"));
	}
}

void MainMenu::updateText() {
	QVector<QString> menuText;
	menuText << "local" << "online" << "textures" << "options" << "quit";

	for(int i=0; i<5; i++) {
		if(m_texts[i])
			m_texts[i]->setPlainText(m_tr->qTranslate("graphic:menu:main:" + menuText[i], m_textures->useAccents()));
		else
			m_texts[i] = addText(m_tr->qTranslate("graphic:menu:main:" + menuText[i], m_textures->useAccents()));

		m_texts[i]->setFont(m_textures->loadFont(50));
		m_texts[i]->setDefaultTextColor(m_textures->primaryColor());
		m_texts[i]->setPos((width() - m_texts[i]->boundingRect().width())/2, topTextY + 75*i);
	}

	m_texts[m_menuIdx]->setDefaultTextColor(m_textures->secondaryColor());
	m_selector->setPos((width() - m_selector->boundingRect().width())/2,
					   m_texts[m_menuIdx]->pos().y() + qAbs(m_texts[m_menuIdx]->boundingRect().height() - m_selector->boundingRect().height())/2);
}

void MainMenu::update() {
	updateTextures();
	updateText();
}

int MainMenu::mouseHoverText(const QPoint &mousePos) {
	int hovered = -1;

	QRect rect(static_cast<int>((width() - m_selector->boundingRect().width())/2),
			   topTextY,
			   m_selector->boundingRect().toRect().width(),
			   m_selector->boundingRect().toRect().height());

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

	for(QGraphicsTextItem* item : m_texts)
		item->setDefaultTextColor(m_textures->primaryColor());
	m_texts[m_menuIdx]->setDefaultTextColor(m_textures->secondaryColor());

	m_selector->setPos((width() - m_selector->boundingRect().width())/2,
					   m_texts[m_menuIdx]->pos().y() + qAbs(m_texts[m_menuIdx]->boundingRect().height() - m_selector->boundingRect().height())/2);
}

void MainMenu::mousePressEvent(QGraphicsSceneMouseEvent* event) {
	int hovered = mouseHoverText(event->scenePos().toPoint());
	if(hovered != -1) {
		switch(hovered) {
		case 3:
			m_game->setGameStatus(ON_OPTIONS_MENU);
			break;

		case 4:
			m_game->setGameStatus(QUIT);
			break;

		default:
			break;
		}

		m_game->update();
	}
}
