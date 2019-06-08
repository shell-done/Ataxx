#ifndef CHARACTERSELECTIONMENU_H
#define CHARACTERSELECTIONMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include "menu.h"
#include "src/Core/gamecore.h"

class CharacterSelectionMenu : public Menu {
	Q_OBJECT

public:
	CharacterSelectionMenu(int width, int height, GameCore* game, QObject* parent);

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
	QGraphicsPixmapItem* m_selector;
	QGraphicsTextItem* m_title;

	QGraphicsRectItem* m_textBox[2];
	QGraphicsTextItem* m_return;
	QGraphicsTextItem* m_start;

	QGraphicsItemGroup* m_playersGroup[4];
	QGraphicsItemGroup* m_thumbsGroup[20];
	QGraphicsItemGroup* m_grid;

public slots:
	void update();
};

#endif // CHARACTERSELECTIONMENU_H
