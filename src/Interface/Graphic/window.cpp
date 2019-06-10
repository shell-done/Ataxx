#include "window.h"

const int Window::m_width = 1280;
const int Window::m_height = 720;

Window::Window(GameCore* game) : QGraphicsView(), m_game(game) {
	m_mainMenu = new MainMenu(m_width, m_height, game, this);
	m_partyOptionsMenu = new PartyOptionsMenu(m_width, m_height, game, this);
	m_characterSelectionMenu = new CharacterSelectionMenu(m_width, m_height, game, this);
	m_texturesMenu = new TexturesMenu(m_width, m_height, game, this);
	m_optionsMenu = new OptionsMenu(m_width, m_height, game, this);
	m_boardScreen = new BoardScreen(m_width, m_height, game, this);

	setFixedSize(m_width + 2, m_height + 2);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setMouseTracking(true);
	setScene(m_mainMenu);

	QMediaPlaylist* playlist = new QMediaPlaylist(this);
	playlist->addMedia(m_game->textures()->loadSoundUrl("background_music.wav"));
	playlist->setPlaybackMode(QMediaPlaylist::Loop);

	m_backgroundMusicPlayer = new QMediaPlayer(this);
	m_backgroundMusicPlayer->setPlaylist(playlist);
	m_backgroundMusicPlayer->setVolume(m_game->volume());
	m_backgroundMusicPlayer->play();

	connect(m_game, SIGNAL(volumeChanged(int)), m_backgroundMusicPlayer, SLOT(setVolume(int)));

	connect(m_game, SIGNAL(updateWindow()), this, SLOT(gameUpdate()));
	connect(m_game->textures(), SIGNAL(updateTextures()), this, SLOT(changeMusic()));
}

void Window::gameUpdate() {
	switch(m_game->gameSubSubStatus()) {
	case QUIT:
		close();
		break;

	case ON_MAIN_MENU:
		setScene(m_mainMenu);
		m_mainMenu->update();
		break;

	case LOCAL_OPTIONS:
		setScene(m_partyOptionsMenu);
		m_partyOptionsMenu->update();
		break;

	case LOCAL_CHARACTER_SELECTION:
		setScene(m_characterSelectionMenu);
		m_characterSelectionMenu->update();
		break;

	case LOCAL_IN_GAME:
		setScene(m_boardScreen);
		if(m_prevStatus != LOCAL_IN_GAME)
			m_boardScreen->generateBoard();
		else
			m_boardScreen->update();

		break;

	case ON_TEXTURES_MENU:
		setScene(m_texturesMenu);
		m_texturesMenu->update();
		break;

	case ON_OPTIONS_MENU:
		setScene(m_optionsMenu);
		m_optionsMenu->update();
		break;

	default:
		break;
	}

	m_prevStatus = m_game->gameSubSubStatus();
}

void Window::changeMusic() {
	QMediaPlaylist* playlist = m_backgroundMusicPlayer->playlist();
	playlist->clear();
	playlist->addMedia(m_game->textures()->loadSoundUrl("background_music.wav"));

	m_backgroundMusicPlayer->stop();
	m_backgroundMusicPlayer->setPlaylist(playlist);
	m_backgroundMusicPlayer->play();
}
