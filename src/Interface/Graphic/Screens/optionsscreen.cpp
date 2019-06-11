#include "optionsscreen.h"

const int OptionsScreen::topTitleY = 220;
const int OptionsScreen::topTextY = 330;

OptionsScreen::OptionsScreen(int width, int height, GameCore* game, QObject* parent) : Screen(width, height, game, "menus/main_menu.png", parent) {
	m_title = nullptr;
	m_return = nullptr;

	//Initialise les carousels
	m_carousels[0] = new GraphicsTextCarouselItem(game, QSize(600, 60), "menus/arrow.png", "menus/arrow_onHover.png", "graphic:menu:options:sound", QString::number(m_game->volume()), 40);
	m_carousels[1] = new GraphicsTextCarouselItem(game, QSize(600, 60), "menus/arrow.png", "menus/arrow_onHover.png", "graphic:menu:options:language", m_tr->currentLanguage(m_textures->removeAccents()), 40);
	addItem(m_carousels[0]);
	addItem(m_carousels[1]);

	//Initialise le bouton de retour
	m_return = new GraphicsButtonItem(game, "menus/selector.png", "graphic:menu:global:return", 40);
	addItem(m_return);

	connect(m_carousels[0], SIGNAL(arrowClicked(e_carouselArrow)), this, SLOT(soundCarouselChanged(e_carouselArrow)));
	connect(m_carousels[1], SIGNAL(arrowClicked(e_carouselArrow)), this, SLOT(langCarouselChanged(e_carouselArrow)));
	connect(m_return, SIGNAL(clicked()), this, SLOT(back()));

	update();
}

void OptionsScreen::updateText() {
	//Place les éléments dans la scènes
	generateText(m_title, "graphic:menu:options:title", 60, m_textures->primaryColor());
	hCenter(m_title, topTitleY);
	hCenter(m_carousels[0], topTextY);
	hCenter(m_carousels[1], topTextY + 60);
	hCenter(m_return, static_cast<int>(height() - 50 - m_return->boundingRect().height()));
}

void OptionsScreen::update() {
	//Met tous les éléments à jour
	updateText();

	for(int i=0; i<2; i++)
		m_carousels[i]->update();

	m_return->update();

	Screen::update();
}

void OptionsScreen::soundCarouselChanged(e_carouselArrow arrow) {
	//Augmente / Diminue la musique
	if(arrow == LEFT)
		m_game->addVolume(-5);
	else
		m_game->addVolume(5);

	m_carousels[0]->setValue(QString::number(m_game->volume()).rightJustified(3, ' '));
	update();
}

void OptionsScreen::langCarouselChanged(e_carouselArrow arrow) {
	//Passe à la langue suivante / Précédente
	if(arrow == LEFT)
		m_tr->setPrevLang();
	else
		m_tr->setNextLang();

	m_carousels[1]->setValue(m_tr->currentLanguage(m_textures->removeAccents()));
	update();
}

void OptionsScreen::back() {
	//Retourne à l'écran précédent
	m_game->setGameStatus(ON_MAIN_MENU);
}
