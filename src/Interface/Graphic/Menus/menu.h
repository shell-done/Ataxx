#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "src/Core/gamecore.h"

class Menu : public QGraphicsScene {
	Q_OBJECT

public:
	Menu(int width, int height, GameCore* game, QString backgroundImg, QObject* parent) : QGraphicsScene(parent), m_game(game) {
		setSceneRect(0, 0, width, height);

		m_menuIdx = 0;
		m_textures = m_game->textures();
		m_tr = m_game->tr();

		m_backgroundImg = backgroundImg;
		m_graphicsBackground = addPixmap(m_textures->loadPixmap(m_backgroundImg));
		m_graphicsBackground->setZValue(-1);
	}

	virtual void update() {
		m_graphicsBackground->setPixmap(m_textures->loadPixmap(m_backgroundImg));
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

	void center(QGraphicsItem* item) {
		item->setPos((width() - item->boundingRect().width())/2, (height() - item->boundingRect().height())/2);
	}

	void alignLeft(QGraphicsItem* item, int x, int y) {
		item->setPos(x, y);
	}

	void alignRight(QGraphicsItem* item, int x, int y) {
		item->setPos(width() - x - item->boundingRect().width(), y);
	}

	void adjustRectangles(QGraphicsItem* item, QGraphicsItem* ref) {
		int x = ref->pos().toPoint().x() + static_cast<int>(ref->boundingRect().width() - item->boundingRect().width())/2;
		int y = ref->pos().toPoint().y() + static_cast<int>(ref->boundingRect().height() - item->boundingRect().height())/2;

		item->setPos(x,y);
	}


protected:
	GameCore* m_game;
	Translator* m_tr;
	Textures* m_textures;

	QString m_backgroundImg;
	QGraphicsPixmapItem* m_graphicsBackground;

	int m_menuIdx;
};

#endif
