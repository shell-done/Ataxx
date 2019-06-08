#ifndef CHARACTERSELECTIONMENU_H
#define CHARACTERSELECTIONMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include "menu.h"
#include "src/Core/gamecore.h"
#include "src/Interface/Graphic/Items/graphicsbutton.h"

class CharacterSelectionMenu : public Menu {
	Q_OBJECT

public:
	CharacterSelectionMenu(int width, int height, GameCore* game, QObject* parent);

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

	QPair<int, int> mouseOverElement(const QPoint& mousePos);

	void createPlayersGroup();
	void createThumbsGroup();
	void displayGroups();

	QPair<int, int> m_elementHover;

	QGraphicsPixmapItem* m_background;
	QGraphicsTextItem* m_title;

	GraphicsButton* m_buttons[2];

	QGraphicsItemGroup* m_playersGroup[4];
	QGraphicsItemGroup* m_thumbsGroup[20];
	QGraphicsItemGroup* m_grid;

private slots:
	void back();
	void next();
};

#endif // CHARACTERSELECTIONMENU_H
