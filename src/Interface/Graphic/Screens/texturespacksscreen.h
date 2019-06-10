#ifndef TEXTURESMENU_H
#define TEXTURESMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include <QCursor>
#include "screen.h"
#include "src/Core/gamecore.h"
#include "src/Interface/Graphic/Items/graphicsbuttonitem.h"

class TexturesPacksScreen : public Screen {
	Q_OBJECT

public:
	TexturesPacksScreen(int width, int height, GameCore* game, QObject* parent);

	void update();

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

	int mouseOverText(const QPoint& mousePos);
	int mouseOverArrow(const QPoint& mousePos);

	QGraphicsTextItem* m_title;
	GraphicsButtonItem* m_return;
	QGraphicsPixmapItem* m_arrows[2];

	QGraphicsPixmapItem* m_packSelected;

	QList<QGraphicsItemGroup*> m_packs;

	int m_packIdx;

private slots:
	void back();

};

#endif // TEXTURESMENU_H
