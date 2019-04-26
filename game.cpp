#include "game.h"

using namespace std;

Game::Game(QObject *parent) : QObject(parent), translator(DIR_LANGUAGES) {
	gameStatus = ON_MAIN_MENU;

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
			gameStatus = IG_LOCAL;
			break;

		case 2:
			gameStatus = IG_ONLINE;
			break;

		case 3:
			gameStatus = ON_TEXTURES_MENU;
			break;

		case 4:
			gameStatus = ON_OPTIONS_MENU;
			optionStatus = NONE;
			break;

		default:
			cout << translator.stdTranslate("console:global:error") << endl;
			uinput = -1;
		}
	} while(uinput == -1);
}

void Game::displayOptions() {
	switch(optionStatus) {
	case NONE:
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
		case NONE:
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
				optionStatus = NONE;
				break;
			}

			QStringList langs = translator.getAvailableLanguages();

			if(uinput >= 1 && uinput <= langs.size()) {
				translator.setLang(langs[uinput-1]);
				optionStatus = NONE;
			} else {
				cout << translator.stdTranslate("console:global:error") << endl;
				uinput = -1;
			}

			break;
		}
	} while(uinput == -1);
}

