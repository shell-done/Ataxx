#ifndef WINDOW_H
#define WINDOW_H

/*!
 * \file window.h
 * \brief Fichier de la classe Window.h
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QGraphicsView>
#include <QColor>
#include <QIcon>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "src/Core/gamecore.h"
#include "Screens/mainmenuscreen.h"
#include "Screens/partyoptionsscreen.h"
#include "Screens/characterselectionscreen.h"
#include "Screens/texturespacksscreen.h"
#include "Screens/optionsscreen.h"
#include "Screens/boardscreen.h"

/*!
 * \class Window window.
 * \brief Classe représentant l'interface graphique du jeu
 *
 * La classe affiche passe d'une scène à l'autre et gère la musique de fond
 */
class Window : public QGraphicsView {
	Q_OBJECT
public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe Window
	 *
	 * \param game Un pointeur sur la classe de coeur de jeu
	*/
	Window(GameCore* game);

private:
	static const int m_width; /*!< La largeur de la fenêtre en px*/
	static const int m_height; /*!< La hauteur de la fenêtre en px*/

	e_gameStatus m_prevStatus; /*!< Statut de jeu précédent*/
	GameCore* m_game; /*!< Coeur du jeu*/

	MainMenuScreen* m_mainMenu; /*!< Ecran : Menu principal*/
	PartyOptionsScreen* m_partyOptionsScreen; /*!< Ecran : Options de jeu local*/
	CharacterSelectionScreen* m_characterSelectionScreen; /*!< Ecran : Selection du joueur*/
	TexturesPacksScreen* m_texturesPacksScreen; /*!< Ecran : Pack de texture*/
	OptionsScreen* m_optionsScreen; /*!< Ecran : Options*/
	BoardScreen* m_boardScreen; /*!< Ecran : Jeu*/

	QMediaPlayer* m_backgroundMusicPlayer; /*!< Ecran : Player pour la musique de fond*/

private slots:
	/*!
	 * \brief Met à jour le jeu lorsque le signal updateWindow() est émit par le coeur de jeu
	*/
	void gameUpdate();

	/*!
	 * \brief Met à jour les textures et la musique
	*/
	void changeResources();
};

#endif // WINDOW_H
