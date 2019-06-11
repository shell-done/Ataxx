#ifndef GRAPHICSTEXTCAROUSEL_H
#define GRAPHICSTEXTCAROUSEL_H

/*!
 * \file graphicsplayerframeitem.h
 * \brief Fichier de la classe GraphicsTextCarouselItem
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QCursor>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include "src/Core/gamecore.h"

/*!
 * \enum e_carouselArrow
 * \brief Flèche du carousel
 *
 * Définie les flèches du carousels possibles
 */
typedef enum e_carouselArrow {
	LEFT, /*!< Flèche gauche */
	RIGHT /*!< Flèche droite */
} e_carouselArrow;

/*!
 * \class GraphicsTextCarouselItem graphicstextcarouselitem.h
 * \brief Classe représentant un QGraphicsItem de cadre affichant du texte et une option changeable avec des flèches
 *
 * La classe hérite de QGraphicsRectItem et contient tout le nécessaire pour afficher un texte et une optio à côté.
 * L'option est changeable avec des flèches
 *
 * Merci à Théo pour avoir trouvé le nom
 */
class GraphicsTextCarouselItem : public QObject, public QGraphicsRectItem {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe GraphicsBoardItem
	 *
	 * \param game Un pointeur sur le coeur du jeu
	 * \param size La taille du carousel
	 * \param arrowImg Le nom de l'image de la flèche
	 * \param arrowHoverImg Le nom de l'image de la flèche survolée
	 * \param label Le texte à afficher
	 * \param value L'optio à afficher
	 * \param fontSize La taille de la police
	 * \param parent L'item parent de celui-ci
	*/
	GraphicsTextCarouselItem(GameCore* game, QSize size, QString arrowImg, QString arrowHoverImg, QString label, QString value, int fontSize, QGraphicsItem* parent = nullptr);

	/*!
	 * \brief Change l'option affichée
	 *
	 * \param value La nouvelle option à afficher
	*/
	void setValue(const QString& value);

	/*!
	 * \brief Met à jour le texte et les textures du boutons
	*/
	void update();

protected:
	/*!
	 * \brief Gère l'entrée de la souris au dessus du carousel
	 *
	 * \param event L'évènement généré
	*/
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);

	/*!
	 * \brief Gère la sortie de la souris au dessus du carousel
	 *
	 * \param event L'évènement généré
	*/
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

	/*!
	 * \brief Gère le mouvement de la souris au dessus du carousel
	 *
	 * \param event L'évènement généré
	*/
	void hoverMoveEvent(QGraphicsSceneHoverEvent* event);

	/*!
	 * \brief Gère le click de la souris au dessus du carousel
	 *
	 * \param event L'évènement généré
	*/
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	static const int arrowMargin; /*!< Marge en pixels entre les flèches et le texte */

	/*!
	 * \brief Place les items du carousel
	*/
	void placeCarousel();

	/*!
	 * \brief Renvoie la flèche survolée par la souris
	 *
	 * \param p Les coordonnée de la souris
	 * \return 0 pour la flèche de gauche, 1 pour celle de droite et -1 pour aucune
	*/
	int mouseOnArrow(const QPoint& p);

	Textures* m_textures; /*!< Un pointeur sur la classe de textures du jeu */
	Translator* m_tr; /*!< Un pointeur sur la classe de traduction du jeu */

	int m_fontSize; /*!< Taille de la police en pixels */
	QString m_arrowImg; /*!< Chemin de l'image de la flèche */
	QString m_arrowHoverImg; /*!< Chemin de l'image de la flèche survolée */

	int prevArrowHover; /*!< Précédente flèche survolée */
	QString m_label; /*!< Texte affiché */
	QString m_value; /*!< Option affiché */

	QGraphicsTextItem* m_graphicsLabel; /*!< Item texte affiché */
	QGraphicsTextItem* m_graphicsValue; /*!< Item texte affiché */
	QGraphicsPixmapItem* m_arrowItem[2]; /*!< Images de flèches */

signals:
	void arrowClicked(e_carouselArrow); /*!< Emit lorsqu'une flèche est cliquée */
};

#endif // GRAPHICSTEXTCAROUSEL_H
