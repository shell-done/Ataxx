#include "optionsmenu.h"

const int OptionsMenu::topTitleY = 220;
const int OptionsMenu::topTextY = 320;
const int OptionsMenu::margin = 330;

OptionsMenu::OptionsMenu(int width, int height, Game* game, QObject* parent) : QGraphicsScene (parent) {
	setSceneRect(0, 0, width, height);

	m_game = game;
	m_tr = game->tr();
	m_textures = game->textures();

	m_background = nullptr;
	m_title = nullptr;
	for(int i=0; i<2; i++) {
		m_volume[i] = nullptr;
		m_language[i] = nullptr;
	}
	m_return = nullptr;

	m_menuIdx = 0;

	updateTextures();
	updateText();
	displayArrows(m_volume[1], 10);
	hCenter(m_selector, static_cast<int>(m_return->pos().y() + qAbs(m_return->boundingRect().height() - m_selector->boundingRect().height())/2));
}

void OptionsMenu::updateTextures() {
	if(m_background) {
		m_background->setPixmap(m_textures->loadPixmap("menus/main_menu.png"));
		m_selector->setPixmap(m_textures->loadPixmap("menus/selector.png"));
		m_arrows[0]->setPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 90));
		m_arrows[1]->setPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 270));
	} else {
		m_background = addPixmap(m_textures->loadPixmap("menus/main_menu.png"));
		m_selector = addPixmap(m_textures->loadPixmap("menus/selector.png"));
		m_arrows[0] = addPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 90));
		m_arrows[1] = addPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 270));
	}

	m_selector->hide();
}

void OptionsMenu::generateText(QGraphicsTextItem*& item, QString str, int fontSize, QColor color) {
	if(item)
		item->setPlainText(m_tr->qTranslate(str, m_textures->useAccents()));
	else
		item = addText(m_tr->qTranslate(str, m_textures->useAccents()));

	item->setFont(m_textures->loadFont(fontSize));
	item->setDefaultTextColor(color);
}

void OptionsMenu::hCenter(QGraphicsItem *item, int y) {
	item->setPos((width() - item->boundingRect().width())/2, y);
}

void OptionsMenu::alignLeft(QGraphicsItem* item, int x, int y) {
	item->setPos(x, y);
}

void OptionsMenu::alignRight(QGraphicsItem* item, int x, int y) {
	item->setPos(width() - x - item->boundingRect().width(), y);
}

void OptionsMenu::displayArrows(QGraphicsItem* item, int margin) {
	int y = static_cast<int>(item->y() + qAbs(item->boundingRect().height() - m_arrows[0]->boundingRect().height())/2);

	m_arrows[1]->setPos(item->x() - margin - m_arrows[1]->boundingRect().width(), y);
	m_arrows[0]->setPos(item->x() + margin + item->boundingRect().width(), y);

	m_arrows[0]->show();
	m_arrows[1]->show();
}

void OptionsMenu::updateText() {
	generateText(m_title, "graphic:menu:options:title", 70, m_textures->primaryColor());
	hCenter(m_title, topTitleY);

	generateText(m_volume[0], "graphic:menu:options:sound", 50, m_textures->primaryColor());
	alignLeft(m_volume[0], margin, topTextY);

	generateText(m_volume[1], m_game->volume(), 50, m_textures->primaryColor());
	alignRight(m_volume[1], margin, topTextY);

	generateText(m_language[0], "graphic:menu:options:language", 50, m_textures->primaryColor());
	alignLeft(m_language[0], margin, topTextY + 75);

	generateText(m_language[1], m_tr->currentLanguage(m_textures->useAccents()), 50, m_textures->primaryColor());
	alignRight(m_language[1], margin, topTextY + 75);

	generateText(m_return, "graphic:menu:global:return", 50, m_textures->primaryColor());
	hCenter(m_return, topTextY + static_cast<int>(75*3.5));
}

void OptionsMenu::update() {
	updateTextures();
	updateText();
}

int OptionsMenu::mouseHoverText(const QPoint &mousePos) {
	QVector<QGraphicsTextItem**> options;
	options << m_volume << m_language;

	for(int i = 0; i<options.size(); i++) {	
		QGraphicsTextItem** option = options[i];

		QRectF intersec = option[0]->boundingRect().translated(option[0]->pos()).united(option[1]->boundingRect().translated(option[1]->pos()));
		intersec.translate(-50, 0);
		intersec.setWidth(intersec.width() + 100);

		if(intersec.contains(mousePos))
			return i;
	}

	if(m_selector->boundingRect().translated(m_selector->pos()).contains(mousePos))
		return 2;

	return -1;
}

int OptionsMenu::mouseHoverArrow(const QPoint &mousePos) {
	for(int i=0; i<=1; i++)
		if(m_arrows[i]->boundingRect().translated(m_arrows[i]->pos()).contains(mousePos))
			return i;

	return -1;
}

void OptionsMenu::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	int idx = mouseHoverText(event->scenePos().toPoint());

	if(idx != -1) {
		m_menuIdx = idx;
		m_selector->hide();
		m_return->setDefaultTextColor(m_textures->primaryColor());

		if(idx == 0) {
			displayArrows(m_volume[1], 10);
		} else if(idx == 1) {
			displayArrows(m_language[1], 10);
		} else if(idx == 2) {
			m_arrows[0]->hide();
			m_arrows[1]->hide();
			m_return->setDefaultTextColor(m_textures->secondaryColor());
			m_selector->show();
		}
	}

	int hovered = mouseHoverArrow(event->scenePos().toPoint());
	for(int i=0; i<=1; i++)
		if(i == hovered)
			m_arrows[i]->setPixmap(m_textures->loadRotatePixmap("menus/arrow_hovered.png", 90 + 180*i));
		else
			m_arrows[i]->setPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 90 + 180*i));
}

void OptionsMenu::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	int idx = mouseHoverText(event->scenePos().toPoint());
	if(idx == -1)
		return;

	int arrowPressed = mouseHoverArrow(event->scenePos().toPoint());

	m_menuIdx = idx;
	if(arrowPressed != -1) {
		if(m_menuIdx == 0) {
			if(arrowPressed == 0)
				m_game->addVolume(+5);
			else
				m_game->addVolume(-5);
		} else if(m_menuIdx == 1) {
			if(arrowPressed == 0)
				m_tr->setPrevLang();
			else
				m_tr->setNextLang();
		}

		m_game->update();
	}

	if(idx == 2)
		m_game->setGameStatus(ON_MAIN_MENU);

	mouseMoveEvent(event);
}
