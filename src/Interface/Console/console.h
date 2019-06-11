#ifndef CONSOLE_H
#define CONSOLE_H

/*!
 * \file console.h
 * \brief Fichier de la classe Console
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QObject>
#include "src/Core/gamecore.h"

/*!
 * \class Console console.h
 * \brief Classe représentant l'interface console du jeu
 *
 * La classe contient toutes les méthodes d'affichage et de récupération d'information depuis et dans la console
 */
class Console : public QObject {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe Board
	 *
	 * \param game Un pointeur sur le coeur du jeu
	*/
	Console(GameCore* game, QObject *parent = nullptr);

private:
	/*!
	 * \brief Affiche toutes les informations du menu principal dans la console
	*/
	void displayMainMenu();

	/*!
	 * \brief Affiche toutes les options du en jeu local dans la console
	*/
	void displayLocalGame();

	/*!
	 * \brief Affiche toutes les options du jeu dans la console
	*/
	void displayOptionsMenu();

	/*!
	 * \brief Récupère les entrées utilisateurs lorsqu'il est sur un menu et change le status du jeu en fonction
	*/
	void getUserInput();

	/*!
	 * \brief Agit en fonction des entrées utilisateur sur le menu principal
	*/
	void mainMenuInput(int userInput);

	/*!
	 * \brief Agit en fonction des entrées utilisateur sur les options de jeu en local
	*/
	void localGameInput(int userInput);

	/*!
	 * \brief Agit en fonction des entrées utilisateur sur les options de jeu
	*/
	void optionsMenuInput(int userInput);

	/*!
	 * \brief Affiche le plateau de jeu
	*/
	void displayParty();

	/*!
	 * \brief Récupère les entrées utilisateur pour bouger les pions
	*/
	void playParty();

	GameCore* m_game; /*!< Un pointeur sur le coeur du jeu, pour gérer le plateau, le nombre de joueur etc... */
	Translator* m_tr; /*!< Un pointeur sur la classe de traduction pour y accéder plus rapidement */

private slots:
	/*!
	 * \brief Actualise la console, est appelé lorsque le signal updateConsole() de GameCore est emis
	*/
	void gameUpdate();
};

#endif // CONSOLE_H
