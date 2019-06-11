#ifndef MAINMENU_H
#define MAINMENU_H

/*!
 * \file mainmenuscreen.h
 * \brief Fichier de la classe MainMenuScreen
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "screen.h"
#include "src/Interface/Graphic/Items/graphicsbuttonitem.h"
#include "src/Core/gamecore.h"

/*!
 * \class MainMenuScreen mainmenuscreen.h
 * \brief Classe représentant l'écran principal
 *
 * La classe affiche les boutons pour changer d'écrans
 */
class MainMenuScreen : public Screen {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe MainMenuScreen
	 *
	 * \param width La largeur de la fenêtre
	 * \param height La hauteur de la fenêtre
	 * \param game Un pointeur sur le coeur du jeu
	 * \param parent L'item parent de celui-ci
	*/
	MainMenuScreen(int width, int height, GameCore* game, QObject* parent);

	/*!
	 * \brief Met à jour l'item
	*/
	void update();

private:
	static const int topTextY; /*!< Distance entre le premier texte et le haut de l'écran */

	/*!
	 * \brief Place les boutons sur l'écran
	*/
	void placeButtons();

	GraphicsButtonItem* m_buttons[5]; /*!< Boutons de l'écran principal */

private slots:
	/*!
	 * \brief Va à l'écran options du jeu local
	*/
	void localGame();

	/*!
	 * \brief Va à l'écran pack de textures
	*/
	void texturesPacks();

	/*!
	 * \brief Va à l'écran options
	*/
	void options();

	/*!
	 * \brief Quitte le jeu
	*/
	void quit();
};

#endif // MAINMENU_H
