#ifndef BOARDSCREEN_H
#define BOARDSCREEN_H

#include "menu.h"
#include "src/Interface/Graphic/Items/graphicsbutton.h"
#include "src/Interface/Graphic/Items/graphicsboarditem.h"

class BoardScreen : public Menu {
	Q_OBJECT

public:
	BoardScreen(int width, int height, GameCore* game, QObject* parent);

private:
	void placeItems();

	QGraphicsPixmapItem* m_background;
	GraphicsBoardItem* m_graphicsBoardItem;

	GraphicsButton* m_buttons[2];

public slots:
	void generateBoard();
	void update();

private slots:
	void quit();
};

#endif // BOARDSCREEN_H
