#include "boardscreen.h"

BoardScreen::BoardScreen(int width, int height, GameCore* game, QObject* parent) : Screen(width, height, game, "menus/game_background.png", parent) {
	m_graphicsBoardItem = nullptr;

	for(int i=0; i<4; i++)
		m_graphicsPlayerFrames[i] = nullptr;

	//Démarre le timer
	m_timer = new QTimer(this);
	m_timer->setInterval(1000);
	m_timer->stop();
	//Déclenche la fonction addSecondToTimer() toutes les secondes
	connect(m_timer, SIGNAL(timeout()), this, SLOT(addSecondToTimer()));

	//Définit le texte du timer à 00:00
	m_graphicsTimer = addText("00:00", m_textures->loadFont(50));
	m_graphicsTimer->setDefaultTextColor(m_textures->primaryColor());

	//Charge le cadre du joueur actuel
	m_graphicsCurrentPlayerFrame = new GraphicsPlayerFrameItem(game, QSize(200, 200), 1, 'A', 40);
	addItem(m_graphicsCurrentPlayerFrame);

	//Charge le texte du joueur actuel
	m_graphicsCurrentPlayerText = addText(m_tr->qTranslate("graphic:local:game:currentPlayer", m_textures->removeAccents()).arg(1), m_textures->loadFont(30));
	m_graphicsCurrentPlayerText->setDefaultTextColor(m_textures->primaryColor());

	//Centre le texte
	QTextOption option = m_graphicsCurrentPlayerText->document()->defaultTextOption();
	option.setAlignment(Qt::AlignCenter);
	m_graphicsCurrentPlayerText->document()->setDefaultTextOption(option);

	//Charge les boutons
	m_buttons[0] = new GraphicsButtonItem(game, "menus/half_selector.png", "graphic:local:game:restart", 40);
	m_buttons[1] = new GraphicsButtonItem(game, "menus/half_selector.png", "graphic:local:game:quit", 40);
	addItem(m_buttons[0]);
	addItem(m_buttons[1]);

	//Connecte les boutons
	connect(m_buttons[0], SIGNAL(clicked()), this, SLOT(restart()));
	connect(m_buttons[1], SIGNAL(clicked()), this, SLOT(quit()));

	//Prépare le player pour les bruitages
	m_soundPlayer = new QMediaPlayer(this);
	m_soundPlayer->setVolume(m_game->volume());

	connect(m_game, SIGNAL(volumeChanged(int)), m_soundPlayer, SLOT(setVolume(int)));
}

void BoardScreen::generateBoard() {
	//Fonction utile lorsque le nombre de joueur ou la taille du plateau change

	if(m_graphicsBoardItem) {
		//Si la grille existe déjà, on la supprime
		disconnect(m_graphicsBoardItem, SIGNAL(pawnMoved()), this, SLOT(pawnMoved()));
		removeItem(m_graphicsBoardItem);
		delete m_graphicsBoardItem;

		m_graphicsBoardItem = nullptr;
	}

	//On en recréer une nouvelle
	m_graphicsBoardItem = new GraphicsBoardItem(m_game);
	addItem(m_graphicsBoardItem);
	connect(m_graphicsBoardItem, SIGNAL(pawnMoved()), this, SLOT(pawnMoved()));

	for(int i=0; i<4; i++) {
		if(m_graphicsPlayerFrames[i]) {
			//Si les cadres des joueurs existent, on les supprime
			removeItem(m_graphicsPlayerFrames[i]);
			delete m_graphicsPlayerFrames[i];

			m_graphicsPlayerFrames[i] = nullptr;
		}
	}

	//On réinitialise le timer
	m_minutes = 0;
	m_seconds = 0;
	m_timer->start(1000);
	m_graphicsTimer->setPlainText("00:00");

	//On recréer les cadres des joueurs
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
	//On met à jour tous les items de l'écran
	if(m_graphicsBoardItem)
		m_graphicsBoardItem->updateBoard();

	for(int i=0; i<2; i++)
		m_buttons[i]->update();

	for(int i=0; i<4; i++)
		if(m_graphicsPlayerFrames[i])
			m_graphicsPlayerFrames[i]->update();

	m_graphicsTimer->setDefaultTextColor(m_textures->primaryColor());
	m_graphicsTimer->setFont(m_textures->loadFont(50));

	int currentPlayer = m_game->board()->playersList().indexOf(m_game->board()->currentPlayer()) + 1;
	m_graphicsCurrentPlayerText->setPlainText(m_tr->qTranslate("graphic:local:game:currentPlayer", m_textures->removeAccents()).arg(currentPlayer));
	m_graphicsCurrentPlayerText->setDefaultTextColor(m_textures->primaryColor());
	m_graphicsCurrentPlayerText->setFont(m_textures->loadFont(30));

	m_graphicsCurrentPlayerFrame->update();
	placeItems();

	Screen::update();
}

void BoardScreen::placeItems() {
	// Largeur des colonnes à gauche et droite du plateau
	int columnWidth = static_cast<int>((width() - m_graphicsBoardItem->boundingRect().width() - 40)/2);

	//Place les cadre des joueurs
	for(int i=0; i<m_game->board()->playersNumber(); i++) {
		m_graphicsPlayerFrames[i]->setX((i%2)*148 + 20); // Permet un placement de la forme : 1 2
		m_graphicsPlayerFrames[i]->setY((i>1)*148 + 75); //                                   3 4

		if(m_game->board()->playersNumber() == 2) // S'il n'y a que 2 joueurs, on descend les cadres
			m_graphicsPlayerFrames[i]->setY(120);
	}

	if(m_game->board()->playersNumber() == 3) // S'il y a 3 joueurs, on centre le dernier
		m_graphicsPlayerFrames[2]->setX((columnWidth - m_graphicsPlayerFrames[2]->boundingRect().width())/2 + 11);


	//Position X du timer
	int timerX = static_cast<int>((columnWidth - m_graphicsTimer->boundingRect().width())/2 + 10);
	m_graphicsTimer->setPos(timerX, height() - m_graphicsTimer->boundingRect().height() - 50);


	//Position de la colonne de droite
	int rightColumnX = static_cast<int>(m_graphicsBoardItem->x() + m_graphicsBoardItem->boundingRect().width() + 10);
	int currentPlayerFrameX = rightColumnX + static_cast<int>((columnWidth - m_graphicsCurrentPlayerFrame->boundingRect().width())/2);

	//Définit la position du cadre dans la colonne de droite
	m_graphicsCurrentPlayerFrame->setPos(currentPlayerFrameX, 75);


	m_graphicsCurrentPlayerText->setTextWidth(columnWidth - 30);
	adjustRectangles(m_graphicsCurrentPlayerText, m_graphicsCurrentPlayerFrame);
	m_graphicsCurrentPlayerText->setY(m_graphicsCurrentPlayerFrame->y() + m_graphicsCurrentPlayerFrame->boundingRect().width() + 10);

	int buttonX = static_cast<int>(rightColumnX + (columnWidth - m_buttons[0]->boundingRect().width())/2);
	m_buttons[1]->setPos(buttonX, height() - m_buttons[1]->boundingRect().height() - 50);
	m_buttons[0]->setPos(buttonX, m_buttons[1]->y() - m_buttons[0]->boundingRect().height() - 20);
}


void BoardScreen::addSecondToTimer() {
	//Ajoute une seconde au timer et affiche le nouveau temps
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

	//On actualise les scores
	for(int i=0; i<players.size(); i++)
		m_graphicsPlayerFrames[i]->setScore(pawns[players[i]]);

	m_graphicsCurrentPlayerFrame->setCharacter(m_game->board()->currentPlayer());
	m_graphicsCurrentPlayerFrame->setPlayer(currentPlayer);

	//On affiche le joueur courant
	m_graphicsCurrentPlayerText->setPlainText(m_tr->qTranslate("graphic:local:game:currentPlayer", m_textures->removeAccents()).arg(currentPlayer));

	if(m_game->board()->stopGame()) {
		//Si le jeu est finit, on récupère le gagnant
		char winner = m_game->board()->winner();
		int pWinner = m_game->board()->playersList().indexOf(winner) + 1;

		//On arrete le timer et on bloque le plateau
		m_graphicsBoardItem->block(true);
		m_timer->stop();

		if(winner == 'Z') {
			//En cas d'égalité...
			m_graphicsCurrentPlayerText->setPlainText(m_tr->qTranslate("graphic:local:game:tie", m_textures->removeAccents()));
			m_graphicsCurrentPlayerFrame->setCharacter('Z');
			m_graphicsCurrentPlayerFrame->setPlayer(-1);
		} else {
			m_graphicsCurrentPlayerText->setPlainText(m_tr->qTranslate("graphic:local:game:win", m_textures->removeAccents()).arg(pWinner));
			m_graphicsCurrentPlayerFrame->setCharacter(winner);
			m_graphicsCurrentPlayerFrame->setPlayer(pWinner);
		}

		//On change la couleur du cadre
		m_graphicsCurrentPlayerText->setDefaultTextColor(m_textures->secondaryColor());
		m_graphicsCurrentPlayerFrame->setSelected(true);

		//On joue le son de victoire
		QUrl soundUrl = m_textures->loadSoundUrl("win_sound.wav");
		if(!soundUrl.isEmpty())
			m_soundPlayer->setMedia(soundUrl);
	} else {
		// Si le jeu continue, on fait le bruit d'un mouvement
		QUrl soundUrl = m_textures->loadSoundUrl("move_sound.wav");
		if(!soundUrl.isEmpty())
			m_soundPlayer->setMedia(soundUrl);
	}

	m_soundPlayer->play();
}

void BoardScreen::restart() {
	m_game->board()->reset();

	//Réinitialise le plateau
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
	//Détruit le plateau et retourne au menu principal
	m_game->board()->destroy();
	m_game->setGameStatus(ON_MAIN_MENU);
}
