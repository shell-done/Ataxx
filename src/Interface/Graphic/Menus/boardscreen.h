#ifndef BOARDSCREEN_H
#define BOARDSCREEN_H

#include "menu.h"
#include "src/Interface/Graphic/Items/graphicsboarditem.h"

class BoardScreen : public Menu {
public:
	BoardScreen(int width, int height, GameCore* game, QObject* parent);

private:
	QGraphicsPixmapItem* m_background;
	GraphicsBoardItem* m_graphicsBoardItem;

public slots:
	void generateBoard();
	void update();
};

#endif // BOARDSCREEN_H
