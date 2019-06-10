#ifndef GAME_H
#define GAME_H

/*!
 * \file gamecore.h
 * \brief Fichier de la classe GameCore
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QObject>
#include "translator.h"
#include "textures.h"
#include "board.h"

/*!
 * \enum e_displayMode
 * \brief Mode d'affichage
 *
 * Définie tous les modes d'affichages possible
 */
typedef enum e_displayMode {
	CONSOLE, /*!< Mode console */
	GRAPHIC, /*!< Mode graphique */
	MIXED /*!< Mode mixe (console et graphique) */
} e_displayMode;


/*!
 * \enum e_gameStatus
 * \brief Status du jeu
 *
 * Définie tous les statut de jeu possible.
 * Le premier chiffre représente le statut du jeu
 * Le deuxième, le sous-statut
 * Le troisième, le sous-sous-statut
 */
typedef enum e_gameStatus {
	QUIT = 000, /*!< Quitter */
	ON_MAIN_MENU = 100, /*!< Sur le menu principal */
	LOCAL_PARTY = 200, /*!< Dans la partie "Jeu local" (sur un menu ou en jeu) */
			LOCAL_OPTIONS = 201, /*!< Sur le menu d'option du jeu local */
			LOCAL_CHARACTER_SELECTION = 202, /*!< Sur le menu de sélection du personnage du jeu local */
		LOCAL_IN_GAME = 210, /*!< En jeu local */
	ONLINE_PARTY = 300, /*!< Dans la partie "Jeu en ligne" (sur un menu ou en jeu) */
	ON_TEXTURES_MENU = 400, /*!< Sur le menu des packs de textures */
	ON_OPTIONS_MENU = 500, /*!< Sur le menu des options générales de jeu */
		ON_LANGUAGES_MENU = 510 /*!< Sur le menu de sélection des langues (utilisé uniquement pour l'affichage console) */
} e_gameStatus;


/*!
 * \class GameCore gamecore.h
 * \brief Classe représentant jeu en lui même
 *
 * La classe contient le plateau de jeu ainsi que les textures ou les langues
 */
class GameCore : public QObject {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * \param arguments Les paramètres associés aux valeurs récupérés dans les arguments de ligne de commande
	 * \param parent Parent de l'objet
	*/
	GameCore(const QMap<QString, QString>& arguments, QObject *parent = nullptr);

	/*!
	 * \brief Charge les textures du jeu, doit être appelé après la création d'une QApplication
	*/
	void loadTextures();

	/*!
	 * \brief Appelle les fonctions updateConsole ou updateGraphic en fonction du mode d'affichage
	*/
	void update();

	/*!
	 * \brief Renvoie un pointeur sur l'objet Translator de la classe
	 *
	 * \return Un pointeur sur l'objet Translator
	*/
	Translator* tr() const;

	/*!
	 * \brief Renvoie un pointeur sur l'objet Textures de la classe
	 *
	 * \return Un pointeur sur l'objet Textures
	*/
	Textures* textures() const;

	/*!
	 * \brief Renvoie le mode d'affichage
	 *
	 * \return Une valeur de l'énumération
	*/
	e_displayMode displayMode() const;


	/*!
	 * \brief Renvoie le statut général du jeu (premier chiffre des statut dans l'énumération)
	 *
	 * \return Une valeur de l'énumération
	*/
	e_gameStatus gameStatus() const;

	/*!
	 * \brief Renvoie le sous-statut du jeu (premier et deuxième chiffre des statut dans l'énumération)
	 *
	 * \return Une valeur de l'énumération
	*/
	e_gameStatus gameSubStatus() const;

	/*!
	 * \brief Renvoie le statut exact du jeu
	 *
	 * \return Une valeur de l'énumération
	*/
	e_gameStatus gameSubSubStatus() const;

	/*!
	 * \brief Définie le statut du jeu
	 *
	 * \param Le nouveau statut du jeu
	*/
	void setGameStatus(const e_gameStatus& gameStatus);


	/*!
	 * \brief Ajoute player joueur au jeu
	 *
	 * Après l'appel de cette méthode, les caractères représentants les joueurs seront réinitialisé
	 *
	 * \param Le nombre de joueur à ajouter
	*/
	void addPlayer(int player);

	/*!
	 * \brief Ajoute size en largeur et hauteur au jeu
	 *
	 * \param La taille à ajouter
	*/
	void addSize(int);

	/*!
	 * \brief Inverse le status de l'apparition des murs (si il y avait des murs, il n'y en a plus et inversement)
	*/
	void changeWall();

	/*!
	 * \brief Renvoie le volume du jeu
	 *
	 * \return Le volume du jeu compris entre 0 (pas de son) et 100 (son maximum)
	*/
	int volume();

	/*!
	 * \brief Ajoute volume au volume du jeu
	 *
	 * \param le volume à ajouter
	*/
	void addVolume(int volume);

	/*!
	 * \brief Renvoie un pointeur sur le plateau de jeu
	 *
	 * \return Un pointeur sur le plateau de jeu
	*/
	Board* board();

private:
	static const QString langsDirectory; /*!< Le dossier des fichiers de langues */
	static const QString texturesPacksDirectory; /*!< Le dossier des packs de textures */

	Translator* m_translator; /*!< Un pointeur sur une classe de traduction */
	Textures* m_textures; /*!< Un pointeur sur une classe de texture (non définie si le jeu est en version console) */
	e_displayMode m_displayMode; /*!< Le type d'affichage du jeu */

	e_gameStatus m_gameStatus; /*!< Le status du jeu */
	int m_volume; /*!< Le volume du son du jeu */

	Board m_board; /*!< Le plateau de jeu */

private slots:
	/*!
	 * \brief Envoie le signal de mise à jour de la fenêtre graphique
	*/
	void texturesUpdated();

signals:
	void updateConsole(); /*!< Demande à mettre à jour la console */
	void updateWindow(); /*!< Demande à mettre à jour la fenêtre */
	void volumeChanged(int); /*!< Signifie que le volume a été changé */
};

#endif // GAME_H
