#ifndef TEXTURESMENU_H
#define TEXTURESMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include "menu.h"
#include "src/Core/gamecore.h"

class TexturesMenu : public Menu {
	Q_OBJECT

public:
	TexturesMenu(int width, int height, GameCore* game, QObject* parent);

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	static const int topTitleY;
	static const int topTextY;
	static const int margin;

	void updateTextures();
	void updateText();

	void createPackItems();
	void displayPackItems();

	int mouseHoverText(const QPoint& mousePos);
	int mouseHoverArrow(const QPoint& mousePos);

	QGraphicsPixmapItem* m_background;
	QGraphicsPixmapItem* m_selector;
	QGraphicsTextItem* m_title;
	QGraphicsTextItem* m_return;
	QGraphicsPixmapItem* m_arrows[2];

	QGraphicsPixmapItem* m_packSelected;

	QList<QGraphicsItemGroup*> m_packs;

	int m_packIdx;

public slots:
	void update();
};

#endif // TEXTURESMENU_H
