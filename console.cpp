#include "console.h"

using namespace std;

Console::Console(Game* game, QObject *parent) : QObject(parent), m_game(game) {
	connect(game, SIGNAL(updateConsole()), this, SLOT(gameUpdate()));

	m_tr = game->tr();
	cout << m_tr->stdTranslate("console:global:project") << endl;
}

void Console::gameUpdate() {
	cout << endl << endl;

	switch(m_game->gameStatus()) {
	case QUIT:
		return;

	case ON_MAIN_MENU:
		displayMainMenu();
		break;

	default:
		break;
	}

	if(m_game->displayMode() == CONSOLE)
		getUserInput();
}

void Console::displayMainMenu() {
	cout << m_tr->stdTranslate("console:global:border") << endl;
	cout << m_tr->stdTranslate("console:menu:title") << endl;
	cout << m_tr->stdTranslate("console:global:border") << endl;
	cout << m_tr->stdTranslate("console:global:askChoice") << endl;
	cout << m_tr->stdTranslate("console:menu:local") << endl;
	cout << m_tr->stdTranslate("console:menu:online") << endl;
	cout << m_tr->stdTranslate("console:menu:options") << endl;
	cout << m_tr->stdTranslate("console:menu:quit") << endl;
}

void Console::getUserInput() {
	string userInput = "";

	cout << m_tr->stdTranslate("console:global:in");
	cin >> userInput;
	cin.clear();
	cin.ignore(INT_MAX, '\n');

	int uinput = -1;

	do {
		try {
			uinput = stoi(userInput);
		}
		catch(invalid_argument &e) {cerr << e.what() << endl;}
		catch(out_of_range &e) {cerr << e.what() << endl;}

		if(uinput == -1)
			cout << m_tr->stdTranslate("console:global:error") << endl;
	} while(uinput == -1);


	switch(m_game->gameStatus()) {
	case ON_MAIN_MENU:
		m_game->mainMenuInput(uinput);
		break;

	default:
		cout << m_tr->stdTranslate("console:global:error") << endl;
		m_game->setGameStatus(ON_MAIN_MENU);
	}
}
