#ifndef TEXTURESMENU_H
#define TEXTURESMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include "menu.h"
#include "src/Core/gamecore.h"
#include "src/Interface/Graphic/Items/graphicsbutton.h"

class TexturesMenu : public Menu {
	Q_OBJECT

public:
	TexturesMenu(int width, int height, GameCore* game, QObject* parent);

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

	int mouseHoverText(const QPoint& mousePos);
	int mouseHoverArrow(const QPoint& mousePos);

	QGraphicsTextItem* m_title;
	GraphicsButton* m_ret;
	QGraphicsPixmapItem* m_arrows[2];

	QGraphicsPixmapItem* m_packSelected;

	QList<QGraphicsItemGroup*> m_packs;

	int m_packIdx;

private slots:
	void back();

};

#endif // TEXTURESMENU_H
