#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "screen.h"
#include "src/Interface/Graphic/Items/graphicstextcarouselitem.h"
#include "src/Interface/Graphic/Items/graphicsbuttonitem.h"
#include "src/Core/gamecore.h"

class OptionsScreen : public Screen {
	Q_OBJECT

public:
	OptionsScreen(int width, int height, GameCore* game, QObject* parent);

	void update();

private:
	static const int topTitleY;
	static const int topTextY;

	void updateText();

	QGraphicsPixmapItem* m_background;
	QGraphicsTextItem* m_title;

	GraphicsTextCarouselItem* m_carousels[2];
	GraphicsButtonItem* m_return;

private slots:
	void soundCarouselChanged(e_carouselArrow);
	void langCarouselChanged(e_carouselArrow);
	void back();
};

#endif // OPTIONSMENU_H
