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

	case ON_OPTIONS_MENU:
		displayOptionsMenu();
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

void Console::displayOptionsMenu() {
	switch(m_game->gameSubStatus()) {
	case ON_OPTIONS_MENU:
		cout << m_tr->stdTranslate("console:global:border") << endl;
		cout << m_tr->stdTranslate("console:options:title") << endl;
		cout << m_tr->stdTranslate("console:global:border") << endl;
		cout << m_tr->stdTranslate("console:options:language") << endl;
		cout << m_tr->stdTranslate("console:menu:return") << endl;
		break;

	case ON_LANGUAGES_MENU:
		cout << m_tr->stdTranslate("console:options:languagesAvailable") << endl;
		for(int i=0; i<m_tr->getAvailableLanguages(true).size(); i++)
			cout << QString("%1. %2").arg(i+1).arg(m_tr->getAvailableLanguages(true)[i]).toStdString() << endl;

		cout << m_tr->stdTranslate("console:menu:return") << endl;
		break;

	default:
		cerr << "[WARNING] Unknown status" << endl;
	}
}

void Console::getUserInput() {
	string userInput = "";
	int uinput = -1;

	do {
		cout << m_tr->stdTranslate("console:global:in");
		cin >> userInput;
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		uinput = -1;
		try {
			uinput = stoi(userInput);
		}
		catch(invalid_argument) {}
		catch(out_of_range) {}

		if(uinput == -1)
			cout << m_tr->stdTranslate("console:global:error") << endl;
	} while(uinput == -1);


	switch(m_game->gameStatus()) {
	case ON_MAIN_MENU:
		mainMenuInput(uinput);
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
	switch(userInput) {
	case 0:
		return;

	case 1:
		m_game->setGameStatus(IG_LOCAL);
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

void Console::optionsMenuInput(int userInput) {
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
		if(userInput >= 1 && userInput <= m_tr->getAvailableLanguages().size()) {
			m_tr->setLang(m_tr->getAvailableLanguages()[userInput - 1]);
			m_game->setGameStatus(ON_OPTIONS_MENU);
		} else {
			cout << m_tr->stdTranslate("console:global:error") << endl;
			m_game->setGameStatus(ON_LANGUAGES_MENU);
		}
		break;

	default:
		cerr << "[WARNING] Unknown status" << endl;
	}
}
