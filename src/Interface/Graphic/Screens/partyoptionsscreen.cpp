#include "partyoptionsscreen.h"

const int PartyOptionsScreen::topTitleY = 220;
const int PartyOptionsScreen::topTextY = 330;

PartyOptionsScreen::PartyOptionsScreen(int width, int height, GameCore* game, QObject* parent) : Screen(width, height, game, "menus/main_menu.png", parent) {
	m_title = nullptr;

	m_carousels[0] = new GraphicsTextCarouselItem(game, QSize(600, 60), "menus/arrow.png", "menus/arrow_onHover.png", "graphic:local:menu:players", QString::number(m_game->board()->playersNumber()), 40);
	m_carousels[1] = new GraphicsTextCarouselItem(game, QSize(600, 60), "menus/arrow.png", "menus/arrow_onHover.png", "graphic:local:menu:mapSize", QString("%1x%1").arg(m_game->board()->width()), 40);
	m_carousels[2] = new GraphicsTextCarouselItem(game, QSize(600, 60), "menus/arrow.png", "menus/arrow_onHover.png", "graphic:local:menu:walls", QString("graphic:menu:global:") + (m_game->board()->walls() ? "yes" : "no"), 40);

	for(int i=0; i<3; i++)
		addItem(m_carousels[i]);

	m_buttons[0] = new GraphicsButtonItem(game, "menus/half_selector.png", "graphic:menu:global:return", 40);
	m_buttons[1] = new GraphicsButtonItem(game, "menus/half_selector.png", "graphic:menu:global:next", 40);

	for(int i=0; i<2; i++)
		addItem(m_buttons[i]);

	connect(m_carousels[0], SIGNAL(arrowClicked(e_carouselArrow)), this, SLOT(playersNumberChanged(e_carouselArrow)));
	connect(m_carousels[1], SIGNAL(arrowClicked(e_carouselArrow)), this, SLOT(mapSizeChanged(e_carouselArrow)));
	connect(m_carousels[2], SIGNAL(arrowClicked(e_carouselArrow)), this, SLOT(wallsChanged(e_carouselArrow)));

	connect(m_buttons[0], SIGNAL(clicked()), this, SLOT(back()));
	connect(m_buttons[1], SIGNAL(clicked()), this, SLOT(next()));

	updateText();
}

void PartyOptionsScreen::updateText() {
	generateText(m_title, "graphic:local:menu:title", 50, m_textures->primaryColor());
	hCenter(m_title, topTitleY);

	for(int i=0; i<3; i++)
		hCenter(m_carousels[i], topTextY+60*i);

	alignLeft(m_buttons[0], 330, static_cast<int>(height() - 50 - m_buttons[0]->boundingRect().height()));
	alignRight(m_buttons[1], 330, static_cast<int>(height() - 50 - m_buttons[1]->boundingRect().height()));
}

void PartyOptionsScreen::update() {
	updateText();

	for(int i=0; i<3; i++)
		m_carousels[i]->update();

	for(int i=0; i<2; i++)
		m_buttons[i]->update();

	Screen::update();
}

void PartyOptionsScreen::playersNumberChanged(e_carouselArrow arrow) {
	if(arrow == LEFT)
		m_game->addPlayer(-1);
	else
		m_game->addPlayer(1);

	m_carousels[0]->setValue(QString::number(m_game->board()->playersNumber()));
	update();
}

void PartyOptionsScreen::mapSizeChanged(e_carouselArrow arrow) {
	if(arrow == LEFT)
		m_game->addSize(-1);
	else
		m_game->addSize(1);

	m_carousels[1]->setValue(QString("%1x%1").arg(m_game->board()->width()));
	update();
}

void PartyOptionsScreen::wallsChanged(e_carouselArrow arrow) {
	Q_UNUSED(arrow);
	m_game->changeWall();

	m_carousels[2]->setValue(QString("graphic:menu:global:") + (m_game->board()->walls() ? "yes" : "no"));

	update();
}

void PartyOptionsScreen::back() {
	m_game->setGameStatus(ON_MAIN_MENU);
}

void PartyOptionsScreen::next() {
	m_game->setGameStatus(LOCAL_CHARACTER_SELECTION);
}
