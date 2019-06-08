#include "partyoptionsmenu.h"

const int PartyOptionsMenu::topTitleY = 220;
const int PartyOptionsMenu::topTextY = 320;
const int PartyOptionsMenu::margin = 330;

PartyOptionsMenu::PartyOptionsMenu(int width, int height, GameCore* game, QObject* parent) : Menu(width, height, game, parent) {
	m_background = nullptr;
	m_title = nullptr;

	for(int i=0; i<2; i++) {
		m_players[i] = nullptr;
		m_mapSize[i] = nullptr;
		m_walls[i] = nullptr;
	}

	m_return = nullptr;
	m_next = nullptr;

	updateTextures();
	updateText();
	displayArrows(m_players[1], 10);
}

void PartyOptionsMenu::updateTextures() {
	if(m_background) {
		m_background->setPixmap(m_textures->loadPixmap("menus/main_menu.png"));
		m_selector->setPixmap(m_textures->loadPixmap("menus/half_selector.png"));
		m_arrows[0]->setPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 90));
		m_arrows[1]->setPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 270));
		m_textBox[0]->setRect(m_selector->boundingRect());
		m_textBox[1]->setRect(m_selector->boundingRect());
	} else {
		m_background = addPixmap(m_textures->loadPixmap("menus/main_menu.png"));
		m_selector = addPixmap(m_textures->loadPixmap("menus/half_selector.png"));
		m_arrows[0] = addPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 90));
		m_arrows[1] = addPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 270));
		m_textBox[0] = addRect(m_selector->boundingRect());
		m_textBox[1] = addRect(m_selector->boundingRect());
	}

	for(int i=0; i<2; i++)
		m_textBox[i]->setPen(QPen(Qt::transparent));

	m_selector->hide();
}

void PartyOptionsMenu::displayArrows(QGraphicsItem* item, int margin) {
	int y = static_cast<int>(item->y() + qAbs(item->boundingRect().height() - m_arrows[0]->boundingRect().height())/2);

	m_arrows[1]->setPos(item->x() - margin - m_arrows[1]->boundingRect().width(), y);
	m_arrows[0]->setPos(item->x() + margin + item->boundingRect().width(), y);

	m_arrows[0]->show();
	m_arrows[1]->show();
}

void PartyOptionsMenu::updateText() {
	generateText(m_title, "graphic:local:menu:title", 60, m_textures->primaryColor());
	hCenter(m_title, topTitleY);

	generateText(m_players[0], "graphic:local:menu:players", 50, m_textures->primaryColor());
	alignLeft(m_players[0], margin, topTextY);

	generateText(m_players[1], QString::number(m_game->board()->playersNumber()), 50, m_textures->primaryColor());
	alignRight(m_players[1], margin, topTextY);

	generateText(m_mapSize[0], "graphic:local:menu:mapSize", 50, m_textures->primaryColor());
	alignLeft(m_mapSize[0], margin, topTextY + 75);

	generateText(m_mapSize[1], QString("%1x%1").arg(m_game->board()->width()), 50, m_textures->primaryColor());
	alignRight(m_mapSize[1], margin, topTextY + 75);

	generateText(m_walls[0], "graphic:local:menu:walls", 50, m_textures->primaryColor());
	alignLeft(m_walls[0], margin, topTextY + 150);

	generateText(m_walls[1], QString("graphic:menu:global:") + (m_game->board()->walls() ? "yes" : "no"), 50, m_textures->primaryColor());
	alignRight(m_walls[1], margin, topTextY + 150);

	generateText(m_return, "graphic:menu:global:return", 50, m_textures->primaryColor());
	alignLeft(m_return, margin + 25, topTextY + static_cast<int>(75*3.75));
	adjustRectangles(m_textBox[0], m_return);

	generateText(m_next, "graphic:menu:global:next", 50, m_textures->primaryColor());
	alignRight(m_next, margin + 25, topTextY + static_cast<int>(75*3.75));
	adjustRectangles(m_textBox[1], m_next);
}

void PartyOptionsMenu::update() {
	updateTextures();
	updateText();
}

int PartyOptionsMenu::mouseHoverText(const QPoint &mousePos) {
	QVector<QGraphicsTextItem**> options;
	options << m_players << m_mapSize << m_walls;

	for(int i = 0; i<options.size(); i++) {
		QGraphicsTextItem** option = options[i];

		QRectF intersec = option[0]->boundingRect().translated(option[0]->pos()).united(option[1]->boundingRect().translated(option[1]->pos()));
		intersec.translate(-50, 0);
		intersec.setWidth(intersec.width() + 100);

		if(intersec.contains(mousePos))
			return i;
	}

	for(int i=0; i<2; i++)
		if(m_textBox[i]->boundingRect().translated(m_textBox[i]->pos()).contains(mousePos))
			return i+3;

	return -1;
}

int PartyOptionsMenu::mouseHoverArrow(const QPoint &mousePos) {
	for(int i=0; i<=1; i++)
		if(m_arrows[i]->boundingRect().translated(m_arrows[i]->pos()).contains(mousePos))
			return i;

	return -1;
}

void PartyOptionsMenu::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	int idx = mouseHoverText(event->scenePos().toPoint());

	if(idx != -1) {
		m_menuIdx = idx;
		m_selector->hide();
		m_next->setDefaultTextColor(m_textures->primaryColor());
		m_return->setDefaultTextColor(m_textures->primaryColor());

		if(idx >= 0 && idx <= 2) {
			if(idx == 0) displayArrows(m_players[1], 10);
			if(idx == 1) displayArrows(m_mapSize[1], 10);
			if(idx == 2) displayArrows(m_walls[1], 10);
		} else {
			m_arrows[0]->hide();
			m_arrows[1]->hide();

			if(idx == 3) {
				m_return->setDefaultTextColor(m_textures->secondaryColor());
				m_selector->setPos(m_textBox[0]->pos());
				m_selector->show();
			} else {
				m_next->setDefaultTextColor(m_textures->secondaryColor());
				m_selector->setPos(m_textBox[1]->pos());
				m_selector->show();
			}
		}
	}

	int hovered = mouseHoverArrow(event->scenePos().toPoint());
	for(int i=0; i<=1; i++)
		if(i == hovered)
			m_arrows[i]->setPixmap(m_textures->loadRotatePixmap("menus/arrow_hovered.png", 90 + 180*i));
		else
			m_arrows[i]->setPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 90 + 180*i));
}

void PartyOptionsMenu::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	int idx = mouseHoverText(event->scenePos().toPoint());
	if(idx == -1)
		return;

	int arrowPressed = mouseHoverArrow(event->scenePos().toPoint());

	m_menuIdx = idx;
	if(arrowPressed != -1) {
		if(m_menuIdx == 0) {
			if(arrowPressed == 0) m_game->addPlayer(1);
			else m_game->addPlayer(-1);

		} else if(m_menuIdx == 1) {
			if(arrowPressed == 0) m_game->addSize(1);
			else m_game->addSize(-1);

		} else if(m_menuIdx == 2) {
			m_game->changeWall();
		}

		m_game->update();
	}

	if(idx == 3)
		m_game->setGameStatus(ON_MAIN_MENU);
	else if(idx == 4)
		m_game->setGameStatus(LOCAL_CHARACTER_SELECTION);

	mouseMoveEvent(event);
}
