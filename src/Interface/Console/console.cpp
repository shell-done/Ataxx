#include "console.h"

using namespace std;

Console::Console(GameCore* game, QObject *parent) : QObject(parent), m_game(game) {
	//Connecte le coeur du jeu au slot de mise à jour pour rafraichir le jeu lorsque cela est demandé
	connect(game, SIGNAL(updateConsole()), this, SLOT(gameUpdate()));

	m_tr = game->tr();
	cout << m_tr->stdTranslate("console:global:project") << endl;
}

void Console::gameUpdate() {
	cout << endl << endl;

	//Selon le status du jeu, on aiguille entre différente méthodes
	//Tout d'abord on affiche
	switch(m_game->gameStatus()) {
	case QUIT:
		return;

	case ON_MAIN_MENU:
		displayMainMenu();
		break;

	case LOCAL_PARTY:
		displayLocalGame();
		break;

	case ON_OPTIONS_MENU:
		displayOptionsMenu();
		break;

	default:
		break;
	}

	//Puis, si le jeu est en mode console uniquement
	if(m_game->displayMode() == CONSOLE) {
		//On récupère les entrées utilisateur
		if(m_game->gameSubStatus() == LOCAL_IN_GAME)
			playParty();
		else
			getUserInput();
	}
}

void Console::displayMainMenu() {
	//Affichage du menu
	cout << m_tr->stdTranslate("console:global:border") << endl;
	cout << m_tr->stdTranslate("console:menu:title") << endl;
	cout << m_tr->stdTranslate("console:global:border") << endl;
	cout << m_tr->stdTranslate("console:global:askChoice") << endl;
	cout << m_tr->stdTranslate("console:menu:local") << endl;
	cout << m_tr->stdTranslate("console:menu:online") << endl;
	cout << m_tr->stdTranslate("console:menu:options") << endl;
	cout << m_tr->stdTranslate("console:menu:quit") << endl;
}

void Console::displayLocalGame() {
	switch(m_game->gameSubStatus()) {
	case LOCAL_PARTY:
		//Affichage du menu des options de jeu local
		cout << m_tr->stdTranslate("console:global:border") << endl;
		cout << m_tr->stdTranslate("console:local:title") << endl;
		cout << m_tr->stdTranslate("console:global:border") << endl;
		cout << m_tr->stdTranslate("console:local:start") << endl;
		cout << m_tr->stdTranslate("console:menu:return") << endl;
		break;

	case LOCAL_IN_GAME:
		//Affichage du plateau de jeu
		displayParty();
		break;

	default:
		cerr << "[WARNING] Unknown status" << endl;
	}
}

void Console::displayOptionsMenu() {
	switch(m_game->gameSubStatus()) {
	case ON_OPTIONS_MENU:
		//Affichage des options du jeu
		cout << m_tr->stdTranslate("console:global:border") << endl;
		cout << m_tr->stdTranslate("console:options:title") << endl;
		cout << m_tr->stdTranslate("console:global:border") << endl;
		cout << m_tr->stdTranslate("console:options:language") << endl;
		cout << m_tr->stdTranslate("console:menu:return") << endl;
		break;

	case ON_LANGUAGES_MENU:
		//Affichage des langues disponibles
		cout << m_tr->stdTranslate("console:options:languagesAvailable") << endl;
		for(int i=0; i<m_tr->availableLanguages(false).size(); i++)
			cout << QString("%1. %2").arg(i+1).arg(m_tr->availableLanguages(false)[i]).toStdString() << endl;

		cout << m_tr->stdTranslate("console:menu:return") << endl;
		break;

	default:
		cerr << "[WARNING] Unknown status" << endl;
	}
}


void Console::getUserInput() {
	string userInput = "";
	int uinput = -1;

	do { // Tant que l'entrée utilisateur n'est pas valide
		cout << m_tr->stdTranslate("console:global:in");
		cin >> userInput; // On la demande
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		uinput = -1;
		try {
			uinput = stoi(userInput); // On essaye de convertir l'entrée en nombre
		}
		catch(invalid_argument) {}
		catch(out_of_range) {}

		if(uinput == -1) // Si cela est impossible, alors on affiche une erreur
			cout << m_tr->stdTranslate("console:global:error") << endl;
	} while(uinput == -1);

	//En fonction de l'entrée, on redirige l'entrée
	switch(m_game->gameStatus()) {
	case ON_MAIN_MENU:
		mainMenuInput(uinput);
		break;

	case LOCAL_PARTY:
		localGameInput(uinput);
		break;

	case ON_OPTIONS_MENU:
		optionsMenuInput(uinput);
		break;

	default:
		cout << m_tr->stdTranslate("console:global:error") << endl;
		m_game->setGameStatus(ON_MAIN_MENU);
	}
}

void Console::mainMenuInput(int userInput) {
	//On modifie le status du jeu en fonction de l'entrée de l'utilisateur lorsque le menu est affiché
	switch(userInput) {
	case 0:
		m_game->setGameStatus(QUIT);
		return;

	case 1:
		m_game->setGameStatus(LOCAL_PARTY);
		break;

	case 2:
		cout << m_tr->stdTranslate("console:menu:unavailable") << endl;
		break;

	case 3:
		m_game->setGameStatus(ON_OPTIONS_MENU);
		break;

	default:
		cout << m_tr->stdTranslate("console:global:error") << endl;
		break;
	}
}

void Console::localGameInput(int userInput) {
	//On modifie le status du jeu en fonction de l'entrée de l'utilisateur lorsque les options de jeu local sont affichées
	switch(m_game->gameSubStatus()) {
	case LOCAL_PARTY:
		if(userInput == 0)
			m_game->setGameStatus(ON_MAIN_MENU);
		else if(userInput == 1)
			if(m_game->board()->exists()) {
				cerr << "[WARNING] A board already exists" << endl;
			} else {
				cout << m_tr->qTranslate("console:local:generating", true).arg(m_game->board()->width()).arg(m_game->board()->height()).toStdString() << endl;
				m_game->board()->generate();
				m_game->setGameStatus(LOCAL_IN_GAME);
			}
		else
			cout << m_tr->stdTranslate("console:global:error") << endl;
		break;

	default:
		cerr << "[WARNING] Unknown status" << endl;
	}
}

void Console::optionsMenuInput(int userInput) {
	//On modifie le status du jeu en fonction de l'entrée de l'utilisateur lorsque les options sont affichées
	switch(m_game->gameSubStatus()) {
	case ON_OPTIONS_MENU:
		switch(userInput) {
		case 0:
			m_game->setGameStatus(ON_MAIN_MENU);
			break;

		case 1:
			m_game->setGameStatus(ON_LANGUAGES_MENU);
			break;

		default:
			cout << m_tr->stdTranslate("console:global:error") << endl;
		}
		break;

	case ON_LANGUAGES_MENU:
		if(userInput == 0) {
			m_game->setGameStatus(ON_OPTIONS_MENU);
			break;
		}
		if(userInput >= 1 && userInput <= m_tr->availableLanguages().size()) {
			m_tr->setLang(m_tr->availableLanguages()[userInput - 1]);
			m_game->setGameStatus(ON_OPTIONS_MENU);
		} else {
			cout << m_tr->stdTranslate("console:global:error") << endl;
		}
		break;

	default:
		cerr << "[WARNING] Unknown status" << endl;
	}
}

void Console::displayParty() {
	Board* board = m_game->board();

	if(!board->exists()) // Si le plateau n'existe pas, on ne fait rien
		return;

	cout << endl;
	cout << m_tr->qTranslate("console:local:round", true).arg(board->round()).toStdString() << endl;
	cout << m_tr->stdTranslate("console:local:pawnsLeft");

	//Affichage du nombre de pions par joueur
	QMap<char, int> pawns = board->countPawns();
	for(int i=0; i<pawns.keys().size() - 1; i++) {
		QString player = m_tr->qTranslate("console:local:player", true);
		player += "(%2), ";
		cout << player.arg(pawns.keys()[i]).arg(pawns[pawns.keys()[i]]).toStdString();
	}

	QString player = m_tr->qTranslate("console:local:player", true);
	player += "(%2)";
	cout << player.arg(pawns.lastKey()).arg(pawns[pawns.lastKey()]).toStdString() << endl;


	//On dessine la grille de jeu
	cout << "   ";
	for(int i=1; i<=board->width(); i++)
		cout << i << " ";
	cout << endl;

	cout << "  +";
	for(int i=2; i<=board->width(); i++)
		cout << "--";
	cout << "-+" << endl;

	for(int i=1; i<=board->height(); i++) {
		cout << " " << i << "|";
		for(int j=0; j<board->width() - 1; j++)
			cout << board->boxes()[j][i-1] << " ";

		cout << board->boxes()[board->width() - 1][i-1] << "|" << endl;
	}

	cout << "  +";
	for(int i=2; i<=board->width(); i++)
		cout << "--";
	cout << "-+" << endl << endl;

	//On affiche le joueur actuel
	cout << m_tr->qTranslate("console:local:playing", true).arg(board->currentPlayer()).toStdString() << endl;
}

void Console::playParty() {
	Board* board = m_game->board();
	QPair<QPoint, QPoint> points = QPair<QPoint, QPoint>(QPoint(-1, -1), QPoint(-1, -1));

	do { // Tant que les informations demandées ne sont pas correctes
		QStringList coordinates;
		cout << m_tr->stdTranslate("console:global:in");

		for(int i=0; i<4; i++) { // On demande 4 entrée à l'utilisateur
			string userInput = "";
			cin >> userInput;
			coordinates << QString::fromStdString(userInput);
		}
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		points = board->strToPoints(coordinates); // On transforme ces entrées en pair de point

		if(points.first.x() == -1) // Si les entrées sont invalides, on continu
			cout << m_tr->stdTranslate("console:global:error") << endl;

	} while(points.first.x() == -1);

	if(!board->currentPlayerAllowedMove(points.first, points.second)) { // On vérifie que le coup est possible
		cout << m_tr->stdTranslate("console:local:incorrectMove") << endl;
		return;
	}

	board->playMove(points.first, points.second); // Si oui, on le joue

	if(board->stopGame()) { // Si le jeu est finis, on affiche le plateau une dernière fois avec le gagnant
		displayParty();

		char winner = board->winner();

		if(winner == 'Z') // Message différent en cas d'égalité
			cout << m_tr->stdTranslate("graphic:local:game:tie") << endl;
		else
			cout << m_tr->qTranslate("console:local:win", true).arg(winner).toStdString() << endl;

		board->destroy();
		m_game->setGameStatus(ON_MAIN_MENU);
	}
}
