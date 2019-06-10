#ifndef GRAPHICBOARDITEM_H
#define GRAPHICBOARDITEM_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include "src/Core/gamecore.h"
#include "src/Core/textures.h"


class GraphicsBoardItem : public QObject, public QGraphicsPixmapItem {
	Q_OBJECT

public:
	GraphicsBoardItem(GameCore* game, QGraphicsItem* parent = nullptr);
	~GraphicsBoardItem();

	void updateBoard();
	void block(bool b);

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	static const int maxGridSize;

	void initBackground();
	void initBoxes();

	void boxClicked(QPoint box);
	void displayAllowedBoxes(QPoint src);
	void movePawn(QPoint dest);

	GameCore* m_game;
	Textures* m_texture;

	int m_width;
	int m_boxesSize;
	QGraphicsPixmapItem*** m_boxes;

	bool m_blocked;
	QPoint m_boxClicked;

signals:
	void pawnMoved();
};

#endif // GRAPHICBOARDITEM_H
