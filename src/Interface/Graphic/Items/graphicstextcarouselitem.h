#ifndef GRAPHICSTEXTCAROUSEL_H
#define GRAPHICSTEXTCAROUSEL_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QCursor>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include "src/Core/gamecore.h"

typedef enum e_carouselArrow {LEFT, RIGHT} e_carouselArrow;

//Merci à théo pour avoir trouvé le nom
class GraphicsTextCarouselItem : public QObject, public QGraphicsRectItem {
	Q_OBJECT

public:
	GraphicsTextCarouselItem(GameCore* game, QSize size, QString arrowImg, QString arrowHoverImg, QString label, QString value, int fontSize, QGraphicsItem* parent = nullptr);

	void setValue(const QString& value);

	void update();

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
	void hoverMoveEvent(QGraphicsSceneHoverEvent* event);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	static const int arrowMargin;

	void placeCarousel();
	int mouseOnArrow(const QPoint& p);

	Textures* m_textures;
	Translator* m_tr;

	int m_fontSize;
	QString m_arrowImg;
	QString m_arrowHoverImg;

	int prevArrowHover;
	QString m_label;
	QString m_value;

	QGraphicsTextItem* m_graphicsLabel;
	QGraphicsTextItem* m_graphicsValue;
	QGraphicsPixmapItem* m_arrowItem[2];

signals:
	void arrowClicked(e_carouselArrow);
};

#endif // GRAPHICSTEXTCAROUSEL_H
