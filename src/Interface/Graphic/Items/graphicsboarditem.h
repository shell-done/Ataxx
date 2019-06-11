#ifndef GRAPHICBOARDITEM_H
#define GRAPHICBOARDITEM_H

/*!
 * \file graphicsboarditem.h
 * \brief Fichier de la classe Console
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QObject>
#include <QGraphicsRectItem>
#include <QPainter>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include "src/Core/gamecore.h"
#include "src/Core/textures.h"

/*!
 * \class GraphicsBoardItem graphicsboarditem.h
 * \brief Classe représentant un QGraphicsItem de grille de jeu
 *
 * La classe hérite de QGraphicsPixmapItem et contient tout le nécessaire pour afficher une grille de jeu carrée
 */
class GraphicsBoardItem : public QObject, public QGraphicsPixmapItem {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe GraphicsBoardItem
	 *
	 * \param game Un pointeur sur le coeur du jeu
	 * \param parent L'item parent de celui-ci
	*/
	GraphicsBoardItem(GameCore* game, QGraphicsItem* parent = nullptr);

	/*!
	 * \brief Destructeur
	*/
	~GraphicsBoardItem();

	/*!
	 * \brief Met à jour le tableau et les textures utilisées
	*/
	void updateBoard();

	/*!
	 * \brief Permet de bloquer la grille, empêchant ainsi les joueurs de jouer (utilisé en fin de partie)
	 *
	 * \param b Si b vaut true, alors la grille est bloquée, sinon elle est débloquée
	*/
	void block(bool b);

protected:
	/*!
	 * \brief Gère le click sur la grille
	 *
	 * \param event Evenement généré par le click de la souris
	*/
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	static const int maxGridSize;

	/*!
	 * \brief Initialise le fond de l'item
	*/
	void initBackground();

	/*!
	 * \brief Initialise les cases pouvant accueillir les pions
	*/
	void initBoxes();

	/*!
	 * \brief Agit en fonction des clicks sur les cases
	 *
	 * \param box Case cliquée
	*/
	void boxClicked(QPoint box);

	/*!
	 * \brief Affiche ou désaffiche les points d'arrivée possible
	 *
	 * Affiche les points d'arrivés possibles en semi-transparent
	 * Si des points d'arrivée ont déjà été affiché, alors supprime ces points
	*/
	void displayAllowedBoxes(QPoint src);

	/*!
	 * \brief Bouge le pion
	 *
	 * Le point de départ est m_boxClicked
	 *
	 * \param dest Le point d'arrivé
	*/
	void movePawn(QPoint dest);

	GameCore* m_game; /*!< Un pointeur sur le coeur du jeu */
	Textures* m_texture; /*!< Un pointeur sur le gestionnaire de textures */

	int m_width; /*!< Taille du côté de la grille */
	int m_boxesSize; /*!< Taille en pixel d'une case */
	QGraphicsPixmapItem*** m_boxes; /*!< Tableau 2D de pointeurs sur chaque case de la grille */

	bool m_blocked; /*!< Vaut true si la grille est bloquée, false sinon */
	QPoint m_boxClicked; /*!< Case précédemment cliquée (vaut -1,-1 si aucune case n'a été cliquée) */

signals:
	void pawnMoved(); /*!< Lorsqu'un pion a été bougé */
};

#endif // GRAPHICBOARDITEM_H
