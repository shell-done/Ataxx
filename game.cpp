#include "game.h"

using namespace std;

Game::Game(QObject *parent) : QObject(parent), translator(DIR_LANGUAGES) {
	gameStatus = ON_MENU;

}

Game::~Game() {

}

void Game::play() {
	while(gameStatus!= QUIT) {
		switch(gameStatus) {
		case ON_MENU:
			displayMenu();
			break;

		case QUIT:
		default:
			break;
		}
	}
}

void Game::displayMenu() {
	cout << translator.stdTranslate("console:menu:project") << endl << endl;
	cout << translator.stdTranslate("console:menu:header:1") << endl;
	cout << translator.stdTranslate("console:menu:header:2") << endl;
	cout << translator.stdTranslate("console:menu:header:1") << endl;
	cout << translator.stdTranslate("console:menu:options") << endl;
	cout << "";

	int a;
	cin >> a;
}
