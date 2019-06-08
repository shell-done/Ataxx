#ifndef PARTYOPTIONSMENU_H
#define PARTYOPTIONSMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "menu.h"
#include "src/Interface/Graphic/Items/graphicstextcarousel.h"
#include "src/Interface/Graphic/Items/graphicsbutton.h"
#include "src/Core/gamecore.h"

class PartyOptionsMenu : public Menu {
	Q_OBJECT

public:
	PartyOptionsMenu(int width, int height, GameCore* game, QObject* parent);

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

	GraphicsTextCarousel* m_carousels[3];
	GraphicsButton* m_buttons[2];

private slots:
	void playersNumberChanged(e_carouselArrow);
	void mapSizeChanged(e_carouselArrow);
	void wallsChanged(e_carouselArrow);
	void back();
	void next();
};

#endif // PARTYOPTIONSMENU_H
