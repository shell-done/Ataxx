#include "graphicsbuttonitem.h"

GraphicsButtonItem::GraphicsButtonItem(GameCore* game, QString buttonImg, QString buttonLabel, int fontSize, QGraphicsItem* parent) : QObject(), QGraphicsRectItem(parent) {
	m_textures = game->textures();
	m_tr = game->tr();

	m_imgPath = buttonImg;
	m_label = buttonLabel;

	//Définit la taille du bouton sur la taille de l'image
	setRect(m_textures->loadPixmap(m_imgPath).rect());
	setPen(QPen(Qt::transparent));

	m_hover = false;
	m_disabled = false;

	m_graphicsPixmap = new QGraphicsPixmapItem(this);

	//Ajoute le texte du bouton
	m_fontSize = fontSize;
	m_graphicsLabel = new QGraphicsTextItem(m_tr->qTranslate(m_label, m_textures->removeAccents()), this);

	setCursor(Qt::PointingHandCursor);

	setAcceptHoverEvents(true);
	update();
}

void GraphicsButtonItem::update() {
	QSize size = boundingRect().toRect().size();
	QPixmap backgroundPixmap(size);

	if(!m_hover || m_disabled) // Si non survolé ou désactivé, on n'affiche pas l'image de fond
		backgroundPixmap.fill(Qt::transparent);
	else // Sinon on l'affciche
		backgroundPixmap = m_textures->loadPixmap(m_imgPath);

	//On affiche l'image
	m_graphicsPixmap->setPixmap(backgroundPixmap);

	// On définit le texte du bouton et sa police
	m_graphicsLabel->setPlainText(m_tr->qTranslate(m_label, m_textures->removeAccents()));
	m_graphicsLabel->setFont(m_textures->loadFont(m_fontSize));

	if(!m_disabled) {
		if(m_hover) // Si survolé alors on utilise la couleur secondaire, sinon on utilise la primaire
			m_graphicsLabel->setDefaultTextColor(m_textures->secondaryColor());
		else
			m_graphicsLabel->setDefaultTextColor(m_textures->primaryColor());
	}

	int x = static_cast<int>((size.width() - m_graphicsLabel->boundingRect().width())/2);
	int y = static_cast<int>((size.height() - m_graphicsLabel->boundingRect().height())/2);
	m_graphicsLabel->setPos(x, y);
}

void GraphicsButtonItem::setDisabled(bool d) {
	m_disabled = d;

	if(m_disabled) {
		//Si désactivé, on utilise la couleur tertiaire et on enlève le curseur
		m_graphicsLabel->setDefaultTextColor(m_textures->tertiaryColor());
		setCursor(Qt::ArrowCursor);
	} else {
		m_graphicsLabel->setDefaultTextColor(m_textures->primaryColor());
		setCursor(Qt::PointingHandCursor);
	}
}

bool GraphicsButtonItem::disabled() {
	return m_disabled;
}

void GraphicsButtonItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
	if(!m_disabled) {
		//Si survolé et non désactivé, on met à jour
		m_hover = true;
		update();
	}

	QGraphicsRectItem::hoverEnterEvent(event);
}

void GraphicsButtonItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
	if(!m_disabled) {
		//Si la souris sort de l'item, on met à jour
		m_hover = false;
		update();
	}

	QGraphicsRectItem::hoverLeaveEvent(event);
}

void GraphicsButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	if(!m_disabled) // Si non désactivé, on émet un signal au click
		emit clicked();

	QGraphicsRectItem::mousePressEvent(event);
}
