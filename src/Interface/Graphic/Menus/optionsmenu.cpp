#include "optionsmenu.h"

const int OptionsMenu::topTitleY = 220;
const int OptionsMenu::topTextY = 330;

OptionsMenu::OptionsMenu(int width, int height, GameCore* game, QObject* parent) : Menu(width, height, game, "menus/main_menu.png", parent) {
	m_background = nullptr;
	m_title = nullptr;
	m_return = nullptr;

	m_carousels[0] = new GraphicsTextCarousel(game, QSize(600, 60), "menus/arrow.png", "menus/arrow_onHover.png", "graphic:menu:options:sound", m_game->volume(), 40);
	m_carousels[1] = new GraphicsTextCarousel(game, QSize(600, 60), "menus/arrow.png", "menus/arrow_onHover.png", "graphic:menu:options:language", m_tr->currentLanguage(m_textures->removeAccents()), 40);
	addItem(m_carousels[0]);
	addItem(m_carousels[1]);

	m_return = new GraphicsButton(game, "menus/selector.png", "graphic:menu:global:return", 40);
	addItem(m_return);

	connect(m_carousels[0], SIGNAL(arrowClicked(e_carouselArrow)), this, SLOT(soundCarouselChanged(e_carouselArrow)));
	connect(m_carousels[1], SIGNAL(arrowClicked(e_carouselArrow)), this, SLOT(langCarouselChanged(e_carouselArrow)));
	connect(m_return, SIGNAL(clicked()), this, SLOT(back()));

	update();
}

void OptionsMenu::updateText() {
	generateText(m_title, "graphic:menu:options:title", 60, m_textures->primaryColor());
	hCenter(m_title, topTitleY);
	hCenter(m_carousels[0], topTextY);
	hCenter(m_carousels[1], topTextY + 60);
	hCenter(m_return, static_cast<int>(height() - 50 - m_return->boundingRect().height()));
}

void OptionsMenu::update() {
	updateText();

	for(int i=0; i<2; i++)
		m_carousels[i]->update();

	m_return->update();

	Menu::update();
}

void OptionsMenu::soundCarouselChanged(e_carouselArrow arrow) {
	if(arrow == LEFT)
		m_game->addVolume(-5);
	else
		m_game->addVolume(5);

	m_carousels[0]->setValue(m_game->volume());
	update();
}

void OptionsMenu::langCarouselChanged(e_carouselArrow arrow) {
	if(arrow == LEFT)
		m_tr->setPrevLang();
	else
		m_tr->setNextLang();

	m_carousels[1]->setValue(m_tr->currentLanguage(m_textures->removeAccents()));
	update();
}

void OptionsMenu::back() {
	m_game->setGameStatus(ON_MAIN_MENU);
}
