#ifndef MAINMENU_H
#define MAINMENU_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "menu.h"
#include "src/Interface/Graphic/Items/graphicsbutton.h"
#include "src/Core/gamecore.h"

class MainMenu : public Menu {
	Q_OBJECT

public:
	MainMenu(int width, int height, GameCore* game, QObject* parent);

	void update();

private:
	static const int topTextY;

	void placeButtons();
	void updateTextures();

	QGraphicsPixmapItem* m_background;
	GraphicsButton* m_buttons[5];

private slots:
	void localGame();
	void texturesPacks();
	void options();
	void quit();
};

#endif // MAINMENU_H
