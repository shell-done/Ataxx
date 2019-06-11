#ifndef PARTYOPTIONSMENU_H
#define PARTYOPTIONSMENU_H

/*!
 * \file partyoptionsscreen.h
 * \brief Fichier de la classe PartyOptionsScreen
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "screen.h"
#include "src/Interface/Graphic/Items/graphicstextcarouselitem.h"
#include "src/Interface/Graphic/Items/graphicsbuttonitem.h"
#include "src/Core/gamecore.h"

/*!
 * \class PartyOptionsScreen partyoptionsscreen.h
 * \brief Classe représentant l'écran des options du jeu local
 *
 * La classe affiche les carousels pour changer les options du jeu local
 */
class PartyOptionsScreen : public Screen {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe PartyOptionsScreen
	 *
	 * \param width La largeur de la fenêtre
	 * \param height La hauteur de la fenêtre
	 * \param game Un pointeur sur le coeur du jeu
	 * \param parent L'item parent de celui-ci
	*/
	PartyOptionsScreen(int width, int height, GameCore* game, QObject* parent);

	/*!
	 * \brief Met à jour l'item
	*/
	void update();

private:
	static const int topTitleY; /*!< Distance entre le haut de l'écran et le titre */
	static const int topTextY; /*!< Distance entre le haut de l'écran et le premier texte */

	/*!
	 * \brief Met à jour le texte de l'item
	*/
	void updateText();

	QGraphicsTextItem* m_title; /*!< Titre de l'écran */

	GraphicsTextCarouselItem* m_carousels[3]; /*!< Carousels des options affichées */
	GraphicsButtonItem* m_buttons[2]; /*!< Boutons de retour et suivant */

private slots:
	/*!
	 * \brief Change le nombre de joueurs
	*/
	void playersNumberChanged(e_carouselArrow);

	/*!
	 * \brief Change la taille de la map
	*/
	void mapSizeChanged(e_carouselArrow);

	/*!
	 * \brief Change le statut des murs
	*/
	void wallsChanged(e_carouselArrow);

	/*!
	 * \brief Passe à l'écran précédent
	*/
	void back();

	/*!
	 * \brief Passe à l'écran suivant
	*/
	void next();
};

#endif // PARTYOPTIONSMENU_H
