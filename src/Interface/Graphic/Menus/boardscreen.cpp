#include "boardscreen.h"

BoardScreen::BoardScreen(int width, int height, GameCore* game, QObject* parent) : Menu(width, height, game, "menus/game_background.png", parent) {
	m_graphicsBoardItem = nullptr;

	for(int i=0; i<4; i++)
		m_graphicsPlayerFrames[i] = nullptr;

	m_timer = new QTimer(this);
	m_timer->setInterval(1000);
	m_timer->stop();
	connect(m_timer, SIGNAL(timeout()), this, SLOT(addSecondToTimer()));

	m_graphicsTimer = addText("00:00", m_textures->loadFont(50));
	m_graphicsTimer->setDefaultTextColor(m_textures->primaryColor());


	m_graphicsCurrentPlayerFrame = new GraphicsPlayerFrameItem(game, QSize(200, 200), 1, 'A', 40);
	addItem(m_graphicsCurrentPlayerFrame);

	m_graphicsCurrentPlayerText = addText(m_tr->qTranslate("graphic:local:game:currentPlayer").arg(1), m_textures->loadFont(30));
	m_graphicsCurrentPlayerText->setDefaultTextColor(m_textures->primaryColor());
	QTextOption option = m_graphicsCurrentPlayerText->document()->defaultTextOption();
	option.setAlignment(Qt::AlignCenter);
	m_graphicsCurrentPlayerText->document()->setDefaultTextOption(option);

	m_buttons[0] = new GraphicsButton(game, "menus/half_selector.png", "graphic:local:game:restart", 40);
	m_buttons[1] = new GraphicsButton(game, "menus/half_selector.png", "graphic:local:game:quit", 40);
	addItem(m_buttons[0]);
	addItem(m_buttons[1]);

	connect(m_buttons[0], SIGNAL(clicked()), this, SLOT(restart()));
	connect(m_buttons[1], SIGNAL(clicked()), this, SLOT(quit()));

	m_soundPlayer = new QMediaPlayer(this);
	m_soundPlayer->setVolume(m_game->volume());

	connect(m_game, SIGNAL(volumeChanged(int)), m_soundPlayer, SLOT(setVolume(int)));
}

void BoardScreen::generateBoard() {
	if(m_graphicsBoardItem) {
		disconnect(m_graphicsBoardItem, SIGNAL(pawnMoved()), this, SLOT(pawnMoved()));
		removeItem(m_graphicsBoardItem);
		delete m_graphicsBoardItem;

		m_graphicsBoardItem = nullptr;
	}

	m_graphicsBoardItem = new GraphicsBoardItem(m_game);
	addItem(m_graphicsBoardItem);
	connect(m_graphicsBoardItem, SIGNAL(pawnMoved()), this, SLOT(pawnMoved()));


	for(int i=0; i<4; i++) {
		if(m_graphicsPlayerFrames[i]) {
			removeItem(m_graphicsPlayerFrames[i]);
			delete m_graphicsPlayerFrames[i];

			m_graphicsPlayerFrames[i] = nullptr;
		}
	}

	m_minutes = 0;
	m_seconds = 0;
	m_timer->start(1000);
	m_graphicsTimer->setPlainText("00:00");

	QVector<char> players = m_game->board()->playersList();
	QMap<char, int> pawns = m_game->board()->countPawns();
	for(int i=0; i<players.size(); i++) {
		m_graphicsPlayerFrames[i] = new GraphicsPlayerFrameItem(m_game, QSize(125, 125), i+1, players[i], 25);
		m_graphicsPlayerFrames[i]->setScore(pawns[players[i]]);
		addItem(m_graphicsPlayerFrames[i]);
	}

	m_graphicsCurrentPlayerFrame->setCharacter(m_game->board()->currentPlayer());

	center(m_graphicsBoardItem);
	update();
}

void BoardScreen::update() {
	if(m_graphicsBoardItem)
		m_graphicsBoardItem->updateBoard();

	for(int i=0; i<2; i++)
		m_buttons[i]->update();

	for(int i=0; i<4; i++)
		if(m_graphicsPlayerFrames[i])
			m_graphicsPlayerFrames[i]->update();

	m_graphicsTimer->setDefaultTextColor(m_textures->primaryColor());
	m_graphicsTimer->setFont(m_textures->loadFont(50));

	m_graphicsCurrentPlayerText->setDefaultTextColor(m_textures->primaryColor());
	m_graphicsCurrentPlayerText->setFont(m_textures->loadFont(30));

	m_graphicsCurrentPlayerFrame->update();
	placeItems();

	Menu::update();
}

void BoardScreen::placeItems() {
	int columnWidth = static_cast<int>((width() - m_graphicsBoardItem->boundingRect().width() - 40)/2);

	for(int i=0; i<m_game->board()->playersNumber(); i++) {
		m_graphicsPlayerFrames[i]->setX((i%2)*148 + 20);
		m_graphicsPlayerFrames[i]->setY((i>1)*148 + 75);

		if(m_game->board()->playersNumber() == 2)
			m_graphicsPlayerFrames[i]->setY(120);
	}

	if(m_game->board()->playersNumber() == 3)
		m_graphicsPlayerFrames[2]->setX((columnWidth - m_graphicsPlayerFrames[2]->boundingRect().width())/2 + 11);


	int timerX = static_cast<int>((columnWidth - m_graphicsTimer->boundingRect().width())/2 + 10);
	m_graphicsTimer->setPos(timerX, height() - m_graphicsTimer->boundingRect().height() - 50);


	int rightColumnX = static_cast<int>(m_graphicsBoardItem->x() + m_graphicsBoardItem->boundingRect().width() + 10);
	int currentPlayerFrameX = rightColumnX + static_cast<int>((columnWidth - m_graphicsCurrentPlayerFrame->boundingRect().width())/2);

	m_graphicsCurrentPlayerFrame->setPos(currentPlayerFrameX, 75);

	m_graphicsCurrentPlayerText->setTextWidth(columnWidth - 30);
	adjustRectangles(m_graphicsCurrentPlayerText, m_graphicsCurrentPlayerFrame);
	m_graphicsCurrentPlayerText->setY(m_graphicsCurrentPlayerFrame->y() + m_graphicsCurrentPlayerFrame->boundingRect().width() + 10);

	int buttonX = static_cast<int>(rightColumnX + (columnWidth - m_buttons[0]->boundingRect().width())/2);
	m_buttons[1]->setPos(buttonX, height() - m_buttons[1]->boundingRect().height() - 50);
	m_buttons[0]->setPos(buttonX, m_buttons[1]->y() - m_buttons[0]->boundingRect().height() - 20);
}


void BoardScreen::addSecondToTimer() {
	m_seconds++;

	if(m_seconds == 60) {
		m_seconds = 0;
		m_minutes++;
	}

	QString sec = (m_seconds > 9 ? QString::number(m_seconds) : "0"+QString::number(m_seconds));
	QString min = (m_minutes > 9 ? QString::number(m_minutes) : "0"+QString::number(m_minutes));

	m_graphicsTimer->setPlainText(min + ":" + sec);
}

void BoardScreen::pawnMoved() {
	QVector<char> players = m_game->board()->playersList();
	QMap<char, int> pawns = m_game->board()->countPawns();

	int currentPlayer = players.indexOf(m_game->board()->currentPlayer()) + 1;

	for(int i=0; i<players.size(); i++)
		m_graphicsPlayerFrames[i]->setScore(pawns[players[i]]);

	m_graphicsCurrentPlayerFrame->setCharacter(m_game->board()->currentPlayer());
	m_graphicsCurrentPlayerFrame->setPlayer(currentPlayer);

	m_graphicsCurrentPlayerText->setPlainText(m_tr->qTranslate("graphic:local:game:currentPlayer").arg(currentPlayer));

	if(m_game->board()->stopGame()) {
		char winner = m_game->board()->winner();
		int pWinner = m_game->board()->playersList().indexOf(winner) + 1;

		m_graphicsBoardItem->block(true);
		m_timer->stop();

		if(winner == 'Z') {
			m_graphicsCurrentPlayerText->setPlainText(m_tr->qTranslate("graphic:local:game:tie"));
			m_graphicsCurrentPlayerFrame->setCharacter('Z');
			m_graphicsCurrentPlayerFrame->setPlayer(-1);
		} else {
			m_graphicsCurrentPlayerText->setPlainText(m_tr->qTranslate("graphic:local:game:win", m_textures->removeAccents()).arg(pWinner));
			m_graphicsCurrentPlayerFrame->setCharacter(winner);
			m_graphicsCurrentPlayerFrame->setPlayer(pWinner);
		}

		m_graphicsCurrentPlayerText->setDefaultTextColor(m_textures->secondaryColor());
		m_graphicsCurrentPlayerFrame->setSelected(true);

		m_soundPlayer->setMedia(m_textures->loadSoundUrl("win_sound.wav"));
	} else {
		m_soundPlayer->setMedia(m_textures->loadSoundUrl("move_sound.wav"));
	}

	m_soundPlayer->play();
}

void BoardScreen::restart() {
	m_game->board()->reset();

	m_graphicsBoardItem->block(false);
	m_graphicsBoardItem->updateBoard();
	pawnMoved();

	m_minutes = 0;
	m_seconds = -1;
	m_timer->start(1000);

	m_graphicsCurrentPlayerText->setDefaultTextColor(m_textures->primaryColor());
	m_graphicsCurrentPlayerFrame->setSelected(false);

	addSecondToTimer();
}

void BoardScreen::quit() {
	m_game->board()->destroy();
	m_game->setGameStatus(ON_MAIN_MENU);
}
