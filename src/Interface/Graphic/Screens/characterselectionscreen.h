#ifndef CHARACTERSELECTIONMENU_H
#define CHARACTERSELECTIONMENU_H

/*!
 * \file characterselectionscreen.h
 * \brief Fichier de la classe CharacterSelectionScreen
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include "screen.h"
#include "src/Core/gamecore.h"
#include "src/Interface/Graphic/Items/graphicsbuttonitem.h"
#include "src/Interface/Graphic/Items/graphicsplayerframeitem.h"

/*!
 * \class CharacterSelectionScreen characterselectionscreen.h
 * \brief Classe représentant l'écran de sélection du personnage
 *
 * La classe affiche la grille des personnages possible et permet aux joueurs de choisir leur personnage
 */
class CharacterSelectionScreen : public Screen {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe BoardScreen
	 *
	 * \param width La largeur de la fenêtre
	 * \param height La hauteur de la fenêtre
	 * \param game Un pointeur sur le coeur du jeu
	 * \param parent L'item parent de celui-ci
	*/
	CharacterSelectionScreen(int width, int height, GameCore* game, QObject* parent);

	/*!
	 * \brief Met à jour l'item
	*/
	void update();

protected:
	/*!
	 * \brief Gère le déplacement de la souris sur la scène
	 *
	 * \param event Evenement généré par le click de la souris
	*/
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

	/*!
	 * \brief Gère le click sur la scène
	 *
	 * \param event Evenement généré par le click de la souris
	*/
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	static const int topTitleY; /*!< Distance entre le haut de l'écran et le titre */
	static const int topTextY; /*!< Distance entre le haut de l'écran et le titre */

	/*!
	 * \brief Met à jour les textures
	*/
	void updateTextures();

	/*!
	 * \brief Met à jour le texte
	*/
	void updateText();

	/*!
	 * \brief Renvoie la miniature survolée par la souris
	 *
	 * \param mousePos Les coordonnée de la souris
	 * \return int Le numéro de la miniature cliquée, -1 si aucune
	*/
	int mouseOverThumb(const QPoint& mousePos);

	/*!
	 * \brief Créer la grille de pions
	*/
	void createThumbsGroup();

	/*!
	 * \brief Affiche la grille de pions et les cadres
	*/
	void displayGroups();


	int m_playersDisplayed; /*!< Nombre de joueurs affichés */
	int m_playerSelected; /*!< Joueur sélectionné */

	QGraphicsTextItem* m_title; /*!< Titre de l'écran */

	GraphicsButtonItem* m_buttons[2]; /*!< Boutons précédant et suivant */
	GraphicsPlayerFrameItem* m_playersGroup[4]; /*!< Cadre des joueurs */

	QGraphicsItemGroup* m_thumbsGroup[20]; /*!< Pions */
	QGraphicsItemGroup* m_grid; /*!< Grille de pions */

private slots:
	/*!
	 * \brief Retour à l'écran précédent
	*/
	void back();

	/*!
	 * \brief Passe à l'écran suivant
	*/
	void next();

	/*!
	 * \brief Appelé lorsqu'un joueur a été sélectionné
	*/
	void characterClicked();
};

#endif // CHARACTERSELECTIONMENU_H
