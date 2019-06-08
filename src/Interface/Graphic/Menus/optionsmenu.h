#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "menu.h"
#include "src/Core/gamecore.h"

class OptionsMenu : public Menu {
	Q_OBJECT

public:
	OptionsMenu(int width, int height, GameCore* game, QObject* parent);

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
	QGraphicsTextItem* m_volume[2];
	QGraphicsTextItem* m_language[2];
	QGraphicsTextItem* m_return;

public slots:
	void update();
};

#endif // OPTIONSMENU_H
