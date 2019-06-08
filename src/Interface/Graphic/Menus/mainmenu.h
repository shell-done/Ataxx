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

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	static const int topTextY;

	int mouseHoverText(const QPoint& mousePos);

	void updateTextures();
	void updateText();

	QGraphicsPixmapItem* m_background;
	QGraphicsPixmapItem* m_selector;
	QGraphicsTextItem* m_texts[5];

	GraphicsButton* m_button;

public slots:
	void update();
	void test() {qDebug() << "a";}
};

#endif // MAINMENU_H
