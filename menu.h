#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "game.h"

class Menu : public QGraphicsScene {
	Q_OBJECT

public:
	Menu(int width, int height, Game* game, QObject* parent) : QGraphicsScene(parent), m_game(game) {
		setSceneRect(0, 0, width, height);

		m_menuIdx = 0;
		m_textures = m_game->textures();
		m_tr = m_game->tr();
	}

	void generateText(QGraphicsTextItem*& item, QString str, int fontSize, QColor color) {
		if(item)
			item->setPlainText(m_tr->qTranslate(str, m_textures->useAccents()));
		else
			item = addText(m_tr->qTranslate(str, m_textures->useAccents()));

		item->setFont(m_textures->loadFont(fontSize));
		item->setDefaultTextColor(color);
	}

	void hCenter(QGraphicsItem *item, int y) {
		item->setPos((width() - item->boundingRect().width())/2, y);
	}

	void vCenter(QGraphicsItem *item, int x) {
		item->setPos(x, (height() - item->boundingRect().height())/2);
	}

	void alignLeft(QGraphicsItem* item, int x, int y) {
		item->setPos(x, y);
	}

	void alignRight(QGraphicsItem* item, int x, int y) {
		item->setPos(width() - x - item->boundingRect().width(), y);
	}


protected:
	Game* m_game;
	Translator* m_tr;
	Textures* m_textures;

	int m_menuIdx;
};

#endif
