#ifndef GRAPHICSTEXTCAROUSEL_H
#define GRAPHICSTEXTCAROUSEL_H

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QCursor>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include "src/Core/gamecore.h"
#include "src/Core/textures.h"
#include "src/Core/translator.h"

typedef enum e_carouselArrow {LEFT, RIGHT} e_carouselArrow;

//Merci à théo pour avoir trouvé le nom
class GraphicsTextCarousel : public QObject, public QGraphicsRectItem {
	Q_OBJECT

public:
	GraphicsTextCarousel(GameCore* game, QSize size, QString arrowImg, QString arrowHoverImg, QString label, QString value, int fontSize, QGraphicsItem* parent = nullptr);

	void setValue(const QString& value);

	void update();

	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
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

	QGraphicsTextItem* m_graphicsLabel;
	QGraphicsTextItem* m_graphicsValue;
	QGraphicsPixmapItem* m_arrowItem[2];

signals:
	void arrowClicked(e_carouselArrow);
};

#endif // GRAPHICSTEXTCAROUSEL_H
