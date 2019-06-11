#ifndef GRAPHICSPLAYERFRAMEITEM_H
#define GRAPHICSPLAYERFRAMEITEM_H

/*!
 * \file graphicsplayerframeitem.h
 * \brief Fichier de la classe GraphicsPlayerItemFrame
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QCursor>
#include <QPen>
#include "src/Core/gamecore.h"


/*!
 * \class GraphicsPlayerFrameItem graphicsplayerframeitem.h
 * \brief Classe représentant un QGraphicsItem de cadre affichant une image et du texte
 *
 * La classe hérite de QGraphicsRectItem et contient tout le nécessaire pour afficher un cadre avec le nom du joueur et du texte
 * L'intéraction avec ce cadre est possible
 */
class GraphicsPlayerFrameItem : public QObject, public QGraphicsRectItem {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe GraphicsPlayerFrameItem
	 *
	 * \param game Un pointeur sur le coeur du jeu
	 * \param restSize La taille du cadre
	 * \param player Le numéro du joueur
	 * \param character Le caractère du joueur
	 * \param fontSize La taille de police tu texte
	 * \param parent L'item parent de celui-ci
	*/
	GraphicsPlayerFrameItem(GameCore* game, QSize rectSize, int player, char character, int fontSize, QGraphicsItem* parent = nullptr);

	/*!
	 * \brief Met à jour le texte et les textures du boutons
	*/
	void update();

	/*!
	 * \brief Affiche le score du joueur à côté de son nom
	 *
	 * \param display Si display vaut true, alors le score du joueur est affiché
	*/
	void enableScoreDisplay(bool display);

	/*!
	 * \brief Définit le score du joueur dans le cadre
	 *
	 * \param score Le score du joueur dans le cadre
	*/
	void setScore(int score);

	/*!
	 * \brief Définit si un effet à lieu lors du survol du cadre par la souris
	 *
	 * \param hoverable Si vaut true, alors un effet à lieu lors du survol par la souris
	*/
	void setHoverable(bool hoverable);

	/*!
	 * \brief Vérifie si le cadre est sélectionné ou non
	 *
	 * \return true si la cadre est sélectionné
	*/
	bool selected();

	/*!
	 * \brief Sélectionne le cadre
	 *
	 * \param selected Si vaut true, alors le cadre sera sélectionné
	*/
	void setSelected(bool selected);

	/*!
	 * \brief Définit le caractère utilisé pour afficher l'image du joueur dans le cadre
	 *
	 * \param c Le caractère du joueur
	*/
	void setCharacter(char c);

	/*!
	 * \brief Le caractère du joueur utilisé pour afficher l'image dans le cadre
	*/
	char character();

	/*!
	 * \brief Définit le numéro du joueur dans le cadre
	 *
	 * \param int Le numéro du joueur dans le cadre
	*/
	void setPlayer(int player);

	/*!
	 * \brief Renvoie le numéro du joueur dans le cadre
	 *
	 * \return Le numéro du joueur dans le cadre
	*/
	int player();

protected:
	/*!
	 * \brief Gère l'entrée de la souris au dessus du cadre
	 *
	 * \param event L'évènement généré
	*/
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);

	/*!
	 * \brief Gère la sortie de la souris au dessus du cadre
	 *
	 * \param event L'évènement généré
	*/
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

	/*!
	 * \brief Gère le click de la souris sur le cadre
	 *
	 * \param event L'évènement généré
	*/
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	static const QString characterSelector; /*!< Le nom de l'image du cadre */
	static const QString characterHovered; /*!< Le nom de l'image du cadre survolé */
	static const QString characterSelected; /*!< Le nom de l'image du sélectionné */
	static const QString charactersThumbs; /*!< L'image de la miniature affichée dans le cadre */

	Textures* m_textures; /*!< Un pointeur sur la classe de textures du jeu */
	Translator* m_tr; /*!< Un pointeur sur la classe de traduction du jeu */

	QGraphicsPixmapItem* m_graphicsFrame; /*!< Le cadre */
	QGraphicsPixmapItem* m_graphicsCharacter; /*!< L'image affichée par le cadre */
	QGraphicsTextItem* m_graphicsText; /*!< Le texte affiché par le cadre */

	bool m_isHoverable; /*!< Vaut vrai si le survol de la souris provoque un effet */
	bool m_selected; /*!< Vaut vrai si sélectionné */
	int m_fontSize; /*!< Taille de la police en points */

	int m_player; /*!< Numéro du joueur affiché */
	char m_character; /*!< Caracttère du joueur affiché */
	int m_score; /*!< Score du joueur affiché */

signals:
	void clicked(); /*!< Emit lorsqu'un click a lieu sur le cadre et que l'item a l'attribut m_isHoverable à true */
};

#endif // GRAPHICSPLAYERFRAMEITEM_H
