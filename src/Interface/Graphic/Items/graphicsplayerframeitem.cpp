#include "graphicsplayerframeitem.h"

const QString GraphicsPlayerFrameItem::characterSelector = "menus/character_selector.png";
const QString GraphicsPlayerFrameItem::characterHovered = "menus/character_onHover.png";
const QString GraphicsPlayerFrameItem::characterSelected = "menus/character_selected.png";
const QString GraphicsPlayerFrameItem::charactersThumbs = "characters/thumbs/%1.png";

GraphicsPlayerFrameItem::GraphicsPlayerFrameItem(GameCore* game, QSize rectSize, int player, char character, int fontSize, QGraphicsItem* parent) : QObject(), QGraphicsRectItem(parent) {
	m_textures = game->textures();
	m_tr = game->tr();
	m_player = player;
	m_character = character;

	m_isHoverable = false;
	m_selected = false;

	m_score = -1;
	m_fontSize = fontSize;

	m_graphicsCharacter = new QGraphicsPixmapItem(m_textures->loadPixmap(charactersThumbs.arg(character)).scaled(rectSize), this);
	m_graphicsFrame = new QGraphicsPixmapItem(m_textures->loadPixmap(characterSelector).scaled(rectSize), this);
	m_graphicsText = new QGraphicsTextItem(m_tr->qTranslate("graphic:local:character:name").arg(player), this);

	setRect(0, 0, rectSize.width(), rectSize.height());
	setPen(QPen(Qt::transparent));

	setAcceptHoverEvents(true);
	update();
}

void GraphicsPlayerFrameItem::update() {
	if(!m_selected) {
		m_graphicsFrame->setPixmap(m_textures->loadPixmap(characterSelector).scaled(boundingRect().size().toSize()));
		m_graphicsText->setDefaultTextColor(m_textures->primaryColor());
	} else {
		m_graphicsFrame->setPixmap(m_textures->loadPixmap(characterSelected).scaled(boundingRect().size().toSize()));
		m_graphicsText->setDefaultTextColor(m_textures->secondaryColor());
	}

	m_graphicsCharacter->setPixmap(m_textures->loadPixmap(charactersThumbs.arg(m_character)).scaled(boundingRect().size().toSize()));

	if(m_score == -1)
		m_graphicsText->setPlainText(m_tr->qTranslate("graphic:local:character:name").arg(m_player));
	else
		m_graphicsText->setPlainText(m_tr->qTranslate("graphic:local:character:name").arg(m_player) + " - " + QString::number(m_score));

	m_graphicsText->setFont(m_textures->loadFont(m_fontSize));

	int x = static_cast<int>((boundingRect().width() - m_graphicsText->boundingRect().width())/2);
	int y = static_cast<int>(boundingRect().height() - m_graphicsText->boundingRect().height());

	m_graphicsText->setPos(x, y);
}

void GraphicsPlayerFrameItem::enableScoreDisplay(bool display) {
	if(display)
		m_score = (m_score == -1 ? 0 : m_score);
	else
		m_score = -1;

	update();
}

void GraphicsPlayerFrameItem::setScore(int s) {
	m_score = s;
	update();
}

void GraphicsPlayerFrameItem::setHoverable(bool hoverable) {
	m_isHoverable = hoverable;

	if(hoverable)
		setCursor(Qt::PointingHandCursor);
	else
		setCursor(Qt::ArrowCursor);
}

bool GraphicsPlayerFrameItem::selected() {
	return m_selected;
}

void GraphicsPlayerFrameItem::setSelected(bool selected) {
	m_selected = selected;
	update();
}

void GraphicsPlayerFrameItem::setCharacter(char c) {
	m_character = c;
	update();
}

char GraphicsPlayerFrameItem::character() {
	return m_character;
}

void GraphicsPlayerFrameItem::setPlayer(int player) {
	m_player = player;
	update();
}

int GraphicsPlayerFrameItem::player() {
	return m_player;
}

void GraphicsPlayerFrameItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
	if(m_isHoverable && !m_selected) {
		m_graphicsFrame->setPixmap(m_textures->loadPixmap(characterHovered).scaled(boundingRect().size().toSize()));
		m_graphicsText->setDefaultTextColor(m_textures->secondaryColor());
	}

	QGraphicsRectItem::hoverEnterEvent(event);
}

void GraphicsPlayerFrameItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
	if(!m_selected) {
		m_graphicsFrame->setPixmap(m_textures->loadPixmap(characterSelector).scaled(boundingRect().size().toSize()));
		m_graphicsText->setDefaultTextColor(m_textures->primaryColor());
	}

	QGraphicsRectItem::hoverLeaveEvent(event);
}

void GraphicsPlayerFrameItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	if(m_isHoverable) {
		setSelected(true);
		emit clicked();
	}

	QGraphicsRectItem::mousePressEvent(event);
}
