#include "graphicstextcarousel.h"

const int GraphicsTextCarousel::arrowMargin = 16;

GraphicsTextCarousel::GraphicsTextCarousel(GameCore* game, QSize size, QString arrowImg, QString arrowHoverImg, QString label, QString value, int fontSize, QGraphicsItem* parent) : QObject(), QGraphicsRectItem(parent) {
	m_textures = game->textures();
	m_tr = game->tr();

	setRect(0, 0, size.width(), size.height());
	setPen(QPen(Qt::transparent));

	m_fontSize = fontSize;
	m_arrowImg = arrowImg;
	m_arrowHoverImg = arrowHoverImg;
	prevArrowHover = -1;

	m_graphicsLabel = new QGraphicsTextItem(m_tr->qTranslate(label, m_textures->removeAccents()), this);
	m_graphicsLabel->setFont(m_textures->loadFont(fontSize));
	m_graphicsLabel->setDefaultTextColor(m_textures->primaryColor());

	m_graphicsValue = new QGraphicsTextItem(m_tr->qTranslate(value, m_textures->removeAccents()), this);
	m_graphicsValue->setFont(m_textures->loadFont(fontSize));
	m_graphicsValue->setDefaultTextColor(m_textures->primaryColor());

	m_arrowItem[0] = new QGraphicsPixmapItem(m_textures->loadRotatePixmap(arrowImg, -90), this);
	m_arrowItem[1] = new QGraphicsPixmapItem(m_textures->loadRotatePixmap(arrowImg, 90), this);

	for(int i=0; i<2; i++) {
		m_arrowItem[i]->hide();
		m_arrowItem[i]->setCursor(Qt::PointingHandCursor);
	}

	setAcceptHoverEvents(true);
	update();
}

void GraphicsTextCarousel::placeCarousel() {
	int textY = static_cast<int>((boundingRect().height() - m_graphicsLabel->boundingRect().height())/2);
	int arrowY = static_cast<int>((boundingRect().height() - m_arrowItem[0]->boundingRect().height())/2);

	m_graphicsLabel->setPos(arrowMargin, textY);

	m_arrowItem[1]->setPos(boundingRect().width() - arrowMargin - m_arrowItem[0]->boundingRect().width(), arrowY);
	m_graphicsValue->setPos(m_arrowItem[1]->x() - m_graphicsValue->boundingRect().width() - 0.5*arrowMargin, textY);

	m_arrowItem[0]->setPos(m_graphicsValue->x() - 0.5*arrowMargin - m_arrowItem[0]->boundingRect().width(), arrowY);
}

int GraphicsTextCarousel::mouseOnArrow(const QPoint& p) {
	for(int i=0; i<2; i++)
		if(m_arrowItem[i]->sceneBoundingRect().contains(p))
			return i;

	return -1;
}

void GraphicsTextCarousel::update() {
	m_arrowItem[0]->setPixmap(m_textures->loadRotatePixmap(m_arrowImg, -90));
	m_arrowItem[1]->setPixmap(m_textures->loadRotatePixmap(m_arrowImg, 90));

	m_graphicsLabel->setDefaultTextColor(m_textures->primaryColor());
	m_graphicsLabel->setFont(m_textures->loadFont(m_fontSize));
	m_graphicsValue->setDefaultTextColor(m_textures->primaryColor());
	m_graphicsValue->setFont(m_textures->loadFont(m_fontSize));

	placeCarousel();
}

void GraphicsTextCarousel::setValue(const QString &value) {
	m_graphicsValue->setPlainText(m_tr->qTranslate(value, m_textures->removeAccents()));
	placeCarousel();
}

void GraphicsTextCarousel::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
	m_arrowItem[0]->show();
	m_arrowItem[1]->show();

	QGraphicsRectItem::hoverEnterEvent(event);
}

void GraphicsTextCarousel::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
	m_arrowItem[0]->hide();
	m_arrowItem[1]->hide();

	if(prevArrowHover != -1)
		m_arrowItem[prevArrowHover]->setPixmap(m_textures->loadRotatePixmap(m_arrowImg, -90 + 180*prevArrowHover));

	prevArrowHover = -1;

	QGraphicsRectItem::hoverLeaveEvent(event);
}

void GraphicsTextCarousel::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
	int arrowHover = mouseOnArrow(event->scenePos().toPoint());

	if(prevArrowHover != -1 && prevArrowHover != arrowHover)
		m_arrowItem[prevArrowHover]->setPixmap(m_textures->loadRotatePixmap(m_arrowImg, -90 + 180*prevArrowHover));

	if(arrowHover != -1)
		m_arrowItem[arrowHover]->setPixmap(m_textures->loadRotatePixmap(m_arrowHoverImg, -90 + 180*arrowHover));

	prevArrowHover = arrowHover;
	QGraphicsRectItem::hoverMoveEvent(event);
}

void GraphicsTextCarousel::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	int arrowHover = mouseOnArrow(event->scenePos().toPoint());

	if(arrowHover == 0)
		emit arrowClicked(LEFT);
	else if(arrowHover == 1)
		emit arrowClicked(RIGHT);

	QGraphicsRectItem::mousePressEvent(event);
	mouseMoveEvent(event);
}
