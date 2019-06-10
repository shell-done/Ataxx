#ifndef MAINMENU_H
#define MAINMENU_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "screen.h"
#include "src/Interface/Graphic/Items/graphicsbuttonitem.h"
#include "src/Core/gamecore.h"

class MainMenuScreen : public Screen {
	Q_OBJECT

public:
	MainMenuScreen(int width, int height, GameCore* game, QObject* parent);

	void update();

private:
	static const int topTextY;

	void placeButtons();

	QGraphicsPixmapItem* m_background;
	GraphicsButtonItem* m_buttons[5];

private slots:
	void localGame();
	void texturesPacks();
	void options();
	void quit();
};

#endif // MAINMENU_H
