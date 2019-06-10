#ifndef WINDOW_H
#define WINDOW_H

#include <QGraphicsView>
#include <QColor>
#include <QIcon>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "src/Core/gamecore.h"
#include "Screens/mainmenuscreen.h"
#include "Screens/partyoptionsscreen.h"
#include "Screens/characterselectionscreen.h"
#include "Screens/texturespacksscreen.h"
#include "Screens/optionsscreen.h"
#include "Screens/boardscreen.h"

class Window : public QGraphicsView {
	Q_OBJECT
public:
	Window(GameCore* game);

private:
	static const int m_width;
	static const int m_height;

	e_gameStatus m_prevStatus;

	GameCore* m_game;
	MainMenuScreen* m_mainMenu;
	PartyOptionsScreen* m_partyOptionsScreen;
	CharacterSelectionScreen* m_characterSelectionScreen;
	TexturesPacksScreen* m_texturesPacksScreen;
	OptionsScreen* m_optionsScreen;
	BoardScreen* m_boardScreen;

	QMediaPlayer* m_backgroundMusicPlayer;

private slots:
	void gameUpdate();
	void changeResources();
};

#endif // WINDOW_H
