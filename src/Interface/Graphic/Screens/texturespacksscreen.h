#ifndef TEXTURESMENU_H
#define TEXTURESMENU_H

/*!
 * \file texturespacksscreen.h
 * \brief Fichier de la classe TexturesPacksScreen.h
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include <QCursor>
#include "screen.h"
#include "src/Core/gamecore.h"
#include "src/Interface/Graphic/Items/graphicsbuttonitem.h"

/*!
 * \class TexturesPacksScreen texturespacksscreen.h
 * \brief Classe représentant l'écran de choix du pack de texture
 *
 * La classe affiche la liste des packs de textures et permet au joueur d'en sélectionner un.
 */
class TexturesPacksScreen : public Screen {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe TexturesPacksScreen
	 *
	 * \param width La largeur de la fenêtre
	 * \param height La hauteur de la fenêtre
	 * \param game Un pointeur sur le coeur du jeu
	 * \param parent L'item parent de celui-ci
	*/
	TexturesPacksScreen(int width, int height, GameCore* game, QObject* parent);

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
	static const int topTextY; /*!< Distance entre le haut de l'écran et le texte */
	static const int margin; /*!< Distance entre les bords latéraux et les items au centre */

	/*!
	 * \brief Met à jour les textures
	*/
	void updateTextures();

	/*!
	 * \brief Met à jour les textes
	*/
	void updateText();

	/*!
	 * \brief Créer la liste des packs
	*/
	void createPackItems();

	/*!
	 * \brief Affiche la liste des packs
	*/
	void displayPackItems();

	/*!
	 * \brief Renvoie le pack survolé par la souris
	 *
	 * \param mousePos La position de la souris
	 * \return L'index du pack survolé, -1 si aucun
	*/
	int mouseOverText(const QPoint& mousePos);

	/*!
	 * \brief Renvoie la flèche survolée par la souris
	 *
	 * \param mousePos La position de la souris
	 * \return L'index de la flèche survolée, -1 si aucun
	*/
	int mouseOverArrow(const QPoint& mousePos);

	QGraphicsTextItem* m_title; /*!< Titre de la scène */
	GraphicsButtonItem* m_return; /*!< Bouton de retour */
	QGraphicsPixmapItem* m_arrows[2]; /*!< Flèches pour voir plus de packs de textures */

	QGraphicsPixmapItem* m_packSelected; /*!< Image derrière le pack sélectionné */

	QList<QGraphicsItemGroup*> m_packs; /*!< Liste des packs */

	int m_packIdx; /*!< Index du défilement de la liste des packs de textures */

private slots:
	void back();

};

#endif // TEXTURESMENU_H
