#include "graphicsbutton.h"

GraphicsButton::GraphicsButton(GameCore* game, QString buttonImg, QString buttonLabel, int fontSize, QGraphicsItem* parent) : QObject(), QGraphicsRectItem(parent) {
	m_textures = game->textures();
	m_tr = game->tr();

	m_imgPath = buttonImg;
	m_label = buttonLabel;

	setRect(m_textures->loadPixmap(m_imgPath).rect());
	setPen(QPen(Qt::transparent));

	m_hover = false;
	m_disabled = false;
	m_clickStart = false;

	m_graphicsPixmap = new QGraphicsPixmapItem(this);

	m_fontSize = fontSize;
	m_graphicsLabel = new QGraphicsTextItem(m_tr->qTranslate(m_label, m_textures->useAccents()), this);

	setCursor(Qt::PointingHandCursor);

	setAcceptHoverEvents(true);
	update();
}

void GraphicsButton::update() {
	QSize size = boundingRect().toRect().size();
	QPixmap backgroundPixmap(size);

	if(!m_hover || m_disabled)
		backgroundPixmap.fill(Qt::transparent);
	else
		backgroundPixmap = m_textures->loadPixmap(m_imgPath);

	m_graphicsPixmap->setPixmap(backgroundPixmap);

	m_graphicsLabel->setPlainText(m_tr->qTranslate(m_label, m_textures->useAccents()));
	m_graphicsLabel->setFont(m_textures->loadFont(m_fontSize));

	if(!m_disabled) {
		if(m_hover)
			m_graphicsLabel->setDefaultTextColor(m_textures->secondaryColor());
		else
			m_graphicsLabel->setDefaultTextColor(m_textures->primaryColor());
	}

	int x = static_cast<int>((size.width() - m_graphicsLabel->boundingRect().width())/2);
	int y = static_cast<int>((size.height() - m_graphicsLabel->boundingRect().height())/2);
	m_graphicsLabel->setPos(x, y);
}

void GraphicsButton::setDisabled(bool d) {
	m_disabled = d;

	if(m_disabled) {
		m_graphicsLabel->setDefaultTextColor(m_textures->tertiaryColor());
		setCursor(Qt::ArrowCursor);
	} else {
		m_graphicsLabel->setDefaultTextColor(m_textures->primaryColor());
		setCursor(Qt::PointingHandCursor);
	}
}

bool GraphicsButton::disabled() {
	return m_disabled;
}

void GraphicsButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
	if(!m_disabled) {
		m_hover = true;
		update();
	}

	QGraphicsRectItem::hoverEnterEvent(event);
}

void GraphicsButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
	if(!m_disabled) {
		m_hover = false;
		update();
	}

	QGraphicsRectItem::hoverLeaveEvent(event);
}

void GraphicsButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	if(!m_disabled)
		emit clicked();

	QGraphicsRectItem::mousePressEvent(event);
}
