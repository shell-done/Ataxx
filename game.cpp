#include "game.h"

using namespace std;

Game::Game(QObject *parent) : QObject(parent), translator(DIR_LANGUAGES) {
	gameStatus = ON_MAIN_MENU;
	board = new Board(this);
}

Game::~Game() {

}

void Game::play() {
	while(gameStatus!= QUIT) {
		switch(gameStatus) {
		case ON_MAIN_MENU:
			displayMenu();
			changeMenu();
			break;

		case ON_LOCAL_MENU:
			displayLocal();
			changeLocal();
			break;

		case ON_TEXTURES_MENU:
			cout << translator.stdTranslate("console:menu:unavailable") << endl;
			gameStatus = ON_MAIN_MENU;
			break;

		case ON_OPTIONS_MENU:
			displayOptions();
			changeOptions();
			break;


		case QUIT:
		default:
			break;
		}
	}
}

int Game::getUserInput() {
	string userInputStr;

	cout << translator.stdTranslate("console:global:in");
	cin >> userInputStr;

	cin.clear();
	cin.ignore(INT_MAX, '\n');

	int userInput = -1;
	try {
		userInput = stoi(userInputStr);
	}
	catch (invalid_argument e) {}
	catch (out_of_range e) {}

	return userInput;
}

void Game::displayMenu() {
	cout << translator.stdTranslate("console:global:project") << endl << endl;
	cout << translator.stdTranslate("console:global:border") << endl;
	cout << translator.stdTranslate("console:menu:title") << endl;
	cout << translator.stdTranslate("console:global:border") << endl;
	cout << translator.stdTranslate("console:global:askChoice") << endl;
	cout << translator.stdTranslate("console:menu:local") << endl;
	cout << translator.stdTranslate("console:menu:online") << endl;
	cout << translator.stdTranslate("console:menu:textures") << endl;
	cout << translator.stdTranslate("console:menu:options") << endl;
	cout << translator.stdTranslate("console:menu:quit") << endl;
}

void Game::changeMenu(int uinput) {
	do {
		if(uinput == -1) {
			uinput = getUserInput();
		}

		switch(uinput) {
		case 0:
			gameStatus = QUIT;
			break;

		case 1:
			gameStatus = ON_LOCAL_MENU;
			localPartyStatus = LOCAL_MENU;
			break;

		case 2:
			gameStatus = IG_ONLINE;
			break;

		case 3:
			gameStatus = ON_TEXTURES_MENU;
			break;

		case 4:
			gameStatus = ON_OPTIONS_MENU;
			optionStatus = OPTIONS_MENU;
			break;

		default:
			cout << translator.stdTranslate("console:global:error") << endl;
			uinput = -1;
		}
	} while(uinput == -1);
}

void Game::displayLocal() {
	switch(localPartyStatus) {
	case LOCAL_MENU:
		cout << endl;
		cout << translator.stdTranslate("console:global:border") << endl;
		cout << translator.stdTranslate("console:local:title") << endl;
		cout << translator.stdTranslate("console:global:border") << endl;
		cout << translator.stdTranslate("console:global:askChoice") << endl;
		cout << translator.stdTranslate("console:local:pvp") << endl;
		cout << translator.stdTranslate("console:local:setsettings") << endl;
		cout << translator.stdTranslate("console:local:displaysettings") << endl;
		cout << translator.stdTranslate("console:menu:return") << endl;
		break;

	case LOCAL_PARTY_SETTINGS:
		cout << endl;
		cout << translator.stdTranslate("console:settings:set:title") << endl;
		cout << translator.stdTranslate("console:settings:set:mapSize") << endl;
		cout << translator.stdTranslate("console:settings:set:P1Character") << endl;
		cout << translator.stdTranslate("console:settings:set:P2Character") << endl;
		cout << translator.stdTranslate("console:menu:return") << endl;
		break;

	case LOCAL_PARTY_MAP:
		cout << translator.stdTranslate("console:settings:set:setMapSize") << endl;
		break;

	case LOCAL_PARTY_P1:
		cout << translator.stdTranslate("console:settings:set:setP1Character") << endl;
		break;

	case LOCAL_PARTY_P2:
		cout << translator.stdTranslate("console:settings:set:setP2Character") << endl;
		break;
	}
}

void Game::changeLocal(int uinput) {
	do {
		if(uinput == -1) {
			uinput = getUserInput();
		}

		switch(localPartyStatus) {
		case LOCAL_MENU:
			switch(uinput) {
			case 0:
				gameStatus = ON_MAIN_MENU;
				break;

			case 1:
				gameStatus = IG_LOCAL;
				break;

			case 2:
				localPartyStatus = LOCAL_PARTY_SETTINGS;
				break;

			case 3:
				cout << endl;
				cout << translator.stdTranslate("console:settings:display:title") << endl;
				cout << translator.qTranslate("console:settings:display:mapSize", true).arg(board->getMapSize().first).arg(board->getMapSize().second).toStdString() << endl;
				cout << translator.qTranslate("console:settings:display:P1Character", true).arg(board->getP1Character()).toStdString() << endl;
				cout << translator.qTranslate("console:settings:display:P1Character", true).arg(board->getP2Character()).toStdString() << endl;
				break;

			default:
				cout << translator.stdTranslate("console:global:error") << endl;
				uinput = -1;
			}
			break;

		case LOCAL_PARTY_SETTINGS:
			switch(uinput) {
			case 0:
				localPartyStatus = LOCAL_MENU;
				break;

			case 1:
				localPartyStatus = LOCAL_PARTY_MAP;
				break;

			case 2:
				localPartyStatus = LOCAL_PARTY_P1;
				break;

			case 3:
				localPartyStatus = LOCAL_PARTY_P2;
				break;

			default:
				cout << translator.stdTranslate("console:global:error") << endl;
				uinput = -1;
			}
			break;

		case LOCAL_PARTY_MAP:
			localPartyStatus = LOCAL_MENU;
			break;

		case LOCAL_PARTY_P1:
			localPartyStatus = LOCAL_MENU;
			break;

		case LOCAL_PARTY_P2:
			localPartyStatus = LOCAL_MENU;
			break;
		}
	} while(uinput == -1);
}

void Game::displayOptions() {
	switch(optionStatus) {
	case OPTIONS_MENU:
		cout << endl << endl;
		cout << translator.stdTranslate("console:global:border") << endl;
		cout << translator.stdTranslate("console:options:title") << endl;
		cout << translator.stdTranslate("console:global:border") << endl;
		cout << translator.stdTranslate("console:global:askChoice") << endl;
		cout << translator.stdTranslate("console:options:language") << endl;
		cout << translator.stdTranslate("console:menu:return") << endl;
		break;

	case SET_LANGUAGE:
		cout << endl;
		cout << translator.stdTranslate("console:options:languagesAvailable") << endl;

		QStringList langs = translator.getAvailableLanguages(true);
		for(int i=0; i<langs.size(); i++)
			cout << QString("%1. %2").arg(i+1).arg(langs[i]).toStdString() << endl;

		cout << translator.stdTranslate("console:menu:return") << endl;

		break;
	}
}

void Game::changeOptions(int uinput) {
	do {
		if(uinput == -1) {
			uinput = getUserInput();
		}

		switch(optionStatus) {
		case OPTIONS_MENU:
			switch(uinput) {
			case 0:
				gameStatus = ON_MAIN_MENU;
				break;

			case 1:
				if(translator.getAvailableLanguages().isEmpty()) {
					cout << "[WARNING] No language available" << endl;
					break;
				}
				optionStatus = SET_LANGUAGE;
				break;

			default:
				cout << translator.stdTranslate("console:global:error") << endl;
				uinput = -1;
			}
			break;

		case SET_LANGUAGE:
			if(uinput == 0) {
				optionStatus = OPTIONS_MENU;
				break;
			}

			QStringList langs = translator.getAvailableLanguages();

			if(uinput >= 1 && uinput <= langs.size()) {
				translator.setLang(langs[uinput-1]);
				optionStatus = OPTIONS_MENU;
			} else {
				cout << translator.stdTranslate("console:global:error") << endl;
				uinput = -1;
			}

			break;
		}
	} while(uinput == -1);
}

