#include "partyoptionsmenu.h"

const int PartyOptionsMenu::topTitleY = 220;
const int PartyOptionsMenu::topTextY = 340;

PartyOptionsMenu::PartyOptionsMenu(int width, int height, GameCore* game, QObject* parent) : Menu(width, height, game, parent) {
	m_background = nullptr;
	m_title = nullptr;

	m_carousels[0] = new GraphicsTextCarousel(game, QSize(700, 60), "menus/arrow.png", "menus/arrow_onHover.png", "graphic:local:menu:players", QString::number(m_game->board()->playersNumber()), 50);
	m_carousels[1] = new GraphicsTextCarousel(game, QSize(700, 60), "menus/arrow.png", "menus/arrow_onHover.png", "graphic:local:menu:mapSize", QString("%1x%1").arg(m_game->board()->width()), 50);
	m_carousels[2] = new GraphicsTextCarousel(game, QSize(700, 60), "menus/arrow.png", "menus/arrow_onHover.png", "graphic:local:menu:walls", QString("graphic:menu:global:") + (m_game->board()->walls() ? "yes" : "no"), 50);

	for(int i=0; i<3; i++)
		addItem(m_carousels[i]);

	m_buttons[0] = new GraphicsButton(game, "menus/half_selector.png", "graphic:menu:global:return", 50);
	m_buttons[1] = new GraphicsButton(game, "menus/half_selector.png", "graphic:menu:global:next", 50);

	for(int i=0; i<2; i++)
		addItem(m_buttons[i]);

	connect(m_carousels[0], SIGNAL(arrowClicked(e_carouselArrow)), this, SLOT(playersNumberChanged(e_carouselArrow)));
	connect(m_carousels[1], SIGNAL(arrowClicked(e_carouselArrow)), this, SLOT(mapSizeChanged(e_carouselArrow)));
	connect(m_carousels[2], SIGNAL(arrowClicked(e_carouselArrow)), this, SLOT(wallsChanged(e_carouselArrow)));

	connect(m_buttons[0], SIGNAL(clicked()), this, SLOT(back()));
	connect(m_buttons[1], SIGNAL(clicked()), this, SLOT(next()));

	updateTextures();
	updateText();
}

void PartyOptionsMenu::updateTextures() {
	if(m_background) {
		m_background->setPixmap(m_textures->loadPixmap("menus/main_menu.png"));
		m_background->setZValue(-1);
	} else {
		m_background = addPixmap(m_textures->loadPixmap("menus/main_menu.png"));
	}
}

void PartyOptionsMenu::updateText() {
	generateText(m_title, "graphic:local:menu:title", 60, m_textures->primaryColor());
	hCenter(m_title, topTitleY);

	for(int i=0; i<3; i++)
		hCenter(m_carousels[i], topTextY+70*i);

	alignLeft(m_buttons[0], 330, static_cast<int>(height() - 50 - m_buttons[0]->boundingRect().height()));
	alignRight(m_buttons[1], 330, static_cast<int>(height() - 50 - m_buttons[1]->boundingRect().height()));
}

void PartyOptionsMenu::update() {
	updateTextures();
	updateText();

	for(int i=0; i<3; i++)
		m_carousels[i]->update();

	for(int i=0; i<2; i++)
		m_buttons[i]->update();
}

void PartyOptionsMenu::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
	for(int i=0; i<3; i++)
		if(m_carousels[i]->sceneBoundingRect().contains(event->scenePos()))
			m_carousels[i]->mouseMoveEvent(event);

	QGraphicsScene::mouseMoveEvent(event);
}

void PartyOptionsMenu::playersNumberChanged(e_carouselArrow arrow) {
	if(arrow == LEFT)
		m_game->addPlayer(-1);
	else
		m_game->addPlayer(1);

	m_carousels[0]->setValue(QString::number(m_game->board()->playersNumber()));
	update();
}

void PartyOptionsMenu::mapSizeChanged(e_carouselArrow arrow) {
	if(arrow == LEFT)
		m_game->addSize(-1);
	else
		m_game->addSize(1);

	m_carousels[1]->setValue(QString("%1x%1").arg(m_game->board()->width()));
	update();
}

void PartyOptionsMenu::wallsChanged(e_carouselArrow arrow) {
	Q_UNUSED(arrow);
	m_game->changeWall();

	m_carousels[2]->setValue(QString("graphic:menu:global:") + (m_game->board()->walls() ? "yes" : "no"));

	update();
}

void PartyOptionsMenu::back() {
	m_game->setGameStatus(ON_MAIN_MENU);
}

void PartyOptionsMenu::next() {
	m_game->setGameStatus(LOCAL_CHARACTER_SELECTION);
}
