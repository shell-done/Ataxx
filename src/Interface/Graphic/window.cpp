#include "window.h"

const int Window::m_width = 1280;
const int Window::m_height = 720;

Window::Window(GameCore* game) : QGraphicsView(), m_game(game) {
	setWindowTitle("Ataxx - ISEN Yncréa Ouest Rennes - CIR 2 C++ Project | Alexandre THOMAS");

	m_mainMenu = new MainMenuScreen(m_width, m_height, game, this);
	m_partyOptionsScreen = new PartyOptionsScreen(m_width, m_height, game, this);
	m_characterSelectionScreen = new CharacterSelectionScreen(m_width, m_height, game, this);
	m_texturesPacksScreen = new TexturesPacksScreen(m_width, m_height, game, this);
	m_optionsScreen = new OptionsScreen(m_width, m_height, game, this);
	m_boardScreen = new BoardScreen(m_width, m_height, game, this);

	setFixedSize(m_width + 2, m_height + 2);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	setMouseTracking(true);
	setScene(m_mainMenu);

	QMediaPlaylist* playlist = new QMediaPlaylist(this);
	playlist->setPlaybackMode(QMediaPlaylist::Loop);

	m_backgroundMusicPlayer = new QMediaPlayer(this);
	m_backgroundMusicPlayer->setPlaylist(playlist);
	m_backgroundMusicPlayer->setVolume(m_game->volume());

	changeResources();

	connect(m_game, SIGNAL(volumeChanged(int)), m_backgroundMusicPlayer, SLOT(setVolume(int)));

	connect(m_game, SIGNAL(updateWindow()), this, SLOT(gameUpdate()));
	connect(m_game->textures(), SIGNAL(updateTextures()), this, SLOT(changeResources()));
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
		setScene(m_partyOptionsScreen);
		m_partyOptionsScreen->update();
		break;

	case LOCAL_CHARACTER_SELECTION:
		setScene(m_characterSelectionScreen);
		m_characterSelectionScreen->update();
		break;

	case LOCAL_IN_GAME:
		setScene(m_boardScreen);
		if(m_prevStatus != LOCAL_IN_GAME)
			m_boardScreen->generateBoard();
		else
			m_boardScreen->update();

		break;

	case ON_TEXTURES_MENU:
		setScene(m_texturesPacksScreen);
		m_texturesPacksScreen->update();
		break;

	case ON_OPTIONS_MENU:
		setScene(m_optionsScreen);
		m_optionsScreen->update();
		break;

	default:
		break;
	}

	m_prevStatus = m_game->gameSubSubStatus();
}

void Window::changeResources() {
	setWindowIcon(QIcon(m_game->textures()->loadPixmap("icon.png")));

	QMediaPlaylist* playlist = m_backgroundMusicPlayer->playlist();
	playlist->clear();

	QUrl bgMusicUrl = m_game->textures()->loadSoundUrl("background_music.wav");

	if(!bgMusicUrl.isEmpty())
		playlist->addMedia(bgMusicUrl);

	m_backgroundMusicPlayer->stop();
	m_backgroundMusicPlayer->setPlaylist(playlist);
	m_backgroundMusicPlayer->play();
}
