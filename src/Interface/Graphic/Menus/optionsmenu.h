#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "menu.h"
#include "src/Interface/Graphic/Items/graphicstextcarousel.h"
#include "src/Interface/Graphic/Items/graphicsbutton.h"
#include "src/Core/gamecore.h"

class OptionsMenu : public Menu {
	Q_OBJECT

public:
	OptionsMenu(int width, int height, GameCore* game, QObject* parent);

	void update();

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

private:
	static const int topTitleY;
	static const int topTextY;

	void updateTextures();
	void updateText();

	QGraphicsPixmapItem* m_background;
	QGraphicsTextItem* m_title;

	GraphicsTextCarousel* m_carousels[2];
	GraphicsButton* m_return;

private slots:
	void soundCarouselChanged(e_carouselArrow);
	void langCarouselChanged(e_carouselArrow);
	void back();
};

#endif // OPTIONSMENU_H
