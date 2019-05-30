#ifndef WINDOW_H
#define WINDOW_H

#include <QGraphicsView>
#include <QColor>
#include "game.h"
#include "mainmenu.h"
#include "partyoptionsmenu.h"
#include "characterselectionmenu.h"
#include "texturesmenu.h"
#include "optionsmenu.h"

class Window : public QGraphicsView {
	Q_OBJECT
public:
	Window(Game* game);

private:
	static const int m_width;
	static const int m_height;

	Game* m_game;
	MainMenu* m_mainMenu;
	PartyOptionsMenu* m_partyOptionsMenu;
	CharacterSelectionMenu* m_characterSelectionMenu;
	TexturesMenu* m_texturesMenu;
	OptionsMenu* m_optionsMenu;


private slots:
	void gameUpdate();
};

#endif // WINDOW_H
