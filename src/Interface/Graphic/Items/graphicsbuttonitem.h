#ifndef GRAPHICSBUTTON_H
#define GRAPHICSBUTTON_H

/*!
 * \file graphicsbuttonitem.h
 * \brief Fichier de la classe GraphicsButtonItem
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QCursor>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include "src/Core/gamecore.h"

/*!
 * \class GraphicsButtonItem graphicsbuttonitem.h
 * \brief Classe représentant un QGraphicsItem de bouton
 *
 * La classe hérite de QGraphicsRectItem et contient tout le nécessaire pour afficher un bouton et réagir au click et survol de la souris
 */
class GraphicsButtonItem : public QObject, public QGraphicsRectItem {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe GraphicsButtonItem
	 *
	 * \param game Un pointeur sur le coeur du jeu
	 * \param imgPath Le nom de l'image affichée lorsque l'image est survolée
	 * \param label Le texte dans le bouton
	 * \param fontSize La taille du texte dans le bouton
	 * \param parent L'item parent de celui-ci
	*/
	GraphicsButtonItem(GameCore* game, QString imgPath, QString label, int fontSize, QGraphicsItem* parent = nullptr);

	/*!
	 * \brief Met à jour le texte et les textures du boutons
	*/
	void update();

	/*!
	 * \brief Désactive le bouton
	 *
	 * \param b Si définie à vrai, alors le bouton est désactivé
	*/
	void setDisabled(bool b);

	/*!
	 * \brief Renvoie le statut d'activation du bouton
	 *
	 * \return true si le bouton est désactivé
	*/
	bool disabled();

protected:
	/*!
	 * \brief Gère l'entrée de la souris au dessus du bouton
	 *
	 * \param event L'évènement généré
	*/
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);

	/*!
	 * \brief Gère la sortie de la souris au dessus du bouton
	 *
	 * \param event L'évènement généré
	*/
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

	/*!
	 * \brief Gère le click de la souris sur le bouton
	 *
	 * \param event L'évènement généré
	*/
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	Textures* m_textures; /*!< Un pointeur sur la classe de textures du jeu */
	Translator* m_tr; /*!< Un pointeur sur la classe de traduction */

	QString m_imgPath; /*!< Le chemin de l'image de fond */

	QGraphicsPixmapItem* m_graphicsPixmap; /*!< L'image de fond */
	QGraphicsTextItem* m_graphicsLabel; /*!< L'item graphique texte du bouton */
	QString m_label; /*!< Le texte du bouton */
	int m_fontSize; /*!< La taille de police */

	bool m_hover; /*!< Vaut vraie si la souris est au dessus du bouton */
	bool m_disabled; /*!< Vaut vraie si le bouton a été désactivé */

signals:
	void clicked(); /*!< Signal émit lors d'un click sur le bouton */
};

#endif // GRAPHICSBUTTON_H
