#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

/*!
 * \file optionsscreen.h
 * \brief Fichier de la classe OptionsScreen
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
 * \class OptionsScreen optionsscreen.h
 * \brief Classe représentant l'écran des options
 *
 * La classe affiche les carousels pour changer les options
 */
class OptionsScreen : public Screen {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe OptionsScreen
	 *
	 * \param width La largeur de la fenêtre
	 * \param height La hauteur de la fenêtre
	 * \param game Un pointeur sur le coeur du jeu
	 * \param parent L'item parent de celui-ci
	*/
	OptionsScreen(int width, int height, GameCore* game, QObject* parent);

	/*!
	 * \brief Met à jour l'item
	*/
	void update();

private:
	static const int topTitleY; /*!< Distance entre le haut de l'écran et le titre */
	static const int topTextY; /*!< Distance entre le haut de l'écran et le premier texte */

	/*!
	 * \brief Met à jour les textes
	*/
	void updateText();

	QGraphicsTextItem* m_title; /*!< Titre de l'écran */

	GraphicsTextCarouselItem* m_carousels[2]; /*!< Options possibles */
	GraphicsButtonItem* m_return; /*!< Bouton de retour */

private slots:
	/*!
	 * \brief Change le son
	*/
	void soundCarouselChanged(e_carouselArrow);

	/*!
	 * \brief Change la langue
	*/
	void langCarouselChanged(e_carouselArrow);

	/*!
	 * \brief Retourne à l'écran précédent
	*/
	void back();
};

#endif // OPTIONSMENU_H
