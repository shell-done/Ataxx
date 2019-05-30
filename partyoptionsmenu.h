#ifndef PARTYOPTIONSMENU_H
#define PARTYOPTIONSMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "menu.h"
#include "game.h"

class PartyOptionsMenu : public Menu {
	Q_OBJECT

public:
	PartyOptionsMenu(int width, int height, Game* game, QObject* parent);

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	static const int topTitleY;
	static const int topTextY;
	static const int margin;

	void displayArrows(QGraphicsItem* item, int margin);

	int mouseHoverText(const QPoint& mousePos);
	int mouseHoverArrow(const QPoint& mousePos);

	void updateTextures();
	void updateText();

	QGraphicsPixmapItem* m_background;
	QGraphicsPixmapItem* m_selector;
	QGraphicsPixmapItem* m_arrows[2];
	QGraphicsTextItem* m_title;
	QGraphicsTextItem* m_players[2];
	QGraphicsTextItem* m_mapSize[2];
	QGraphicsTextItem* m_walls[2];

	QGraphicsRectItem* m_textBox[2];
	QGraphicsTextItem* m_return;
	QGraphicsTextItem* m_next;

public slots:
	void update();
};

#endif // PARTYOPTIONSMENU_H
