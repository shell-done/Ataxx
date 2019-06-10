#ifndef GRAPHICSBUTTON_H
#define GRAPHICSBUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QCursor>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include "src/Core/gamecore.h"

class GraphicsButton : public QObject, public QGraphicsRectItem {
	Q_OBJECT

public:
	GraphicsButton(GameCore* game, QString imgPath, QString label, int fontSize, QGraphicsItem* parent = nullptr);

	void update();

	void setDisabled(bool);
	bool disabled();

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	Textures* m_textures;
	Translator* m_tr;

	QString m_imgPath;

	QGraphicsPixmapItem* m_graphicsPixmap;
	QGraphicsTextItem* m_graphicsLabel;
	QString m_label;
	int m_fontSize;

	bool m_hover;
	bool m_disabled;
	bool m_clickStart;

signals:
	void clicked();
};

#endif // GRAPHICSBUTTON_H
