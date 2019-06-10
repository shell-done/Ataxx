#ifndef WINDOW_H
#define WINDOW_H

#include <QGraphicsView>
#include <QColor>
#include <QIcon>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "src/Core/gamecore.h"
#include "Menus/mainmenu.h"
#include "Menus/partyoptionsmenu.h"
#include "Menus/characterselectionmenu.h"
#include "Menus/texturesmenu.h"
#include "Menus/optionsmenu.h"
#include "Menus/boardscreen.h"

class Window : public QGraphicsView {
	Q_OBJECT
public:
	Window(GameCore* game);

private:
	static const int m_width;
	static const int m_height;

	e_gameStatus m_prevStatus;

	GameCore* m_game;
	MainMenu* m_mainMenu;
	PartyOptionsMenu* m_partyOptionsMenu;
	CharacterSelectionMenu* m_characterSelectionMenu;
	TexturesMenu* m_texturesMenu;
	OptionsMenu* m_optionsMenu;
	BoardScreen* m_boardScreen;

	QMediaPlayer* m_backgroundMusicPlayer;

private slots:
	void gameUpdate();
	void changeResources();
};

#endif // WINDOW_H
