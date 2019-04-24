#include "game.h"

using namespace std;

Game::Game(QObject *parent) : QObject(parent) {
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
	cout << "Ataxx - CIR 2 Project - Alexandre THOMAS | ISEN Yncrea Ouest Rennes" << endl << endl;
	cout << "+-------------------------------------+" << endl;
	cout << "|             Ataxx - Menu            |" << endl;
	cout << "+-------------------------------------+" << endl;
	cout << "Please select any of the following option :" << endl;
	cout << "";

	int a;
	cin >> a;
}
