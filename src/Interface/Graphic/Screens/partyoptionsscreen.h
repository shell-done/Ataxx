#ifndef PARTYOPTIONSMENU_H
#define PARTYOPTIONSMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "screen.h"
#include "src/Interface/Graphic/Items/graphicstextcarouselitem.h"
#include "src/Interface/Graphic/Items/graphicsbuttonitem.h"
#include "src/Core/gamecore.h"

class PartyOptionsScreen : public Screen {
	Q_OBJECT

public:
	PartyOptionsScreen(int width, int height, GameCore* game, QObject* parent);

	void update();

private:
	static const int topTitleY;
	static const int topTextY;

	void updateText();

	QGraphicsTextItem* m_title;

	GraphicsTextCarouselItem* m_carousels[3];
	GraphicsButtonItem* m_buttons[2];

private slots:
	void playersNumberChanged(e_carouselArrow);
	void mapSizeChanged(e_carouselArrow);
	void wallsChanged(e_carouselArrow);
	void back();
	void next();
};

#endif // PARTYOPTIONSMENU_H
