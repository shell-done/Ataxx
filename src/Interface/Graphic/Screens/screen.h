#ifndef MENU_H
#define MENU_H

/*!
 * \file screen.h
 * \brief Fichier de la classe PartyOptionsScreen
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "src/Core/gamecore.h"

/*!
 * \class Screen screen.h
 * \brief Classe représentant un écran du jeu
 *
 * La classe affiche un écran du jeu et possèdent plusieurs méthodes pour faciliter le placement des items
 */
class Screen : public QGraphicsScene {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe Screen
	 *
	 * \param width La largeur de la fenêtre
	 * \param height La hauteur de la fenêtre
	 * \param game Un pointeur sur le coeur du jeu
	 * \param backgroundImg Le nom de l'image de fond
	 * \param parent L'item parent de celui-ci
	*/
	Screen(int width, int height, GameCore* game, QString backgroundImg, QObject* parent) : QGraphicsScene(parent), m_game(game) {
		setSceneRect(0, 0, width, height);

		m_textures = m_game->textures();
		m_tr = m_game->tr();

		m_backgroundImg = backgroundImg;
		m_graphicsBackground = addPixmap(m_textures->loadPixmap(m_backgroundImg));
		m_graphicsBackground->setZValue(-1);
	}

	/*!
	 * \brief Met à jour l'item
	*/
	virtual void update() {
		m_graphicsBackground->setPixmap(m_textures->loadPixmap(m_backgroundImg));
	}

	/*!
	 * \brief Génère ou met à jour un QGraphicsTextItem
	 *
	 * \param item Une référence sur l'item à créer/mettre à jour
	 * \param str Le contenu de l'item
	 * \param fontSize La taille de police en points
	 * \param color La couleur du texte
	*/
	void generateText(QGraphicsTextItem*& item, QString str, int fontSize, QColor color) {
		//Si l'item existe déjà, on le met à jour, sinon on le créer
		if(item)
			item->setPlainText(m_tr->qTranslate(str, m_textures->removeAccents()));
		else
			item = addText(m_tr->qTranslate(str, m_textures->removeAccents()));

		item->setFont(m_textures->loadFont(fontSize));
		item->setDefaultTextColor(color);
	}

	/*!
	 * \brief Centre horizontalement l'item
	*/
	void hCenter(QGraphicsItem *item, int y) {
		item->setPos((width() - item->boundingRect().width())/2, y);
	}

	/*!
	 * \brief Centre verticalement l'item
	*/
	void vCenter(QGraphicsItem *item, int x) {
		item->setPos(x, (height() - item->boundingRect().height())/2);
	}

	/*!
	 * \brief Centre verticalement et horizontalement l'item
	*/
	void center(QGraphicsItem* item) {
		item->setPos((width() - item->boundingRect().width())/2, (height() - item->boundingRect().height())/2);
	}

	/*!
	 * \brief Aligne l'item à gauche (équivalent à setPos)
	*/
	void alignLeft(QGraphicsItem* item, int x, int y) {
		item->setPos(x, y);
	}

	/*!
	 * \brief Aligne l'item à droite
	*/
	void alignRight(QGraphicsItem* item, int x, int y) {
		item->setPos(width() - x - item->boundingRect().width(), y);
	}

	/*!
	 * \brief Ajuste les deux items pour que leur centre soient au même point
	*/
	void adjustRectangles(QGraphicsItem* item, QGraphicsItem* ref) {
		int x = ref->pos().toPoint().x() + static_cast<int>(ref->boundingRect().width() - item->boundingRect().width())/2;
		int y = ref->pos().toPoint().y() + static_cast<int>(ref->boundingRect().height() - item->boundingRect().height())/2;

		item->setPos(x,y);
	}


protected:
	GameCore* m_game; /*!< Un pointeur sur le coeur du jeu */
	Translator* m_tr; /*!< Un pointeur sur la classe de traduction */
	Textures* m_textures; /*!< Un pointeur sur la classe de textures */

	QString m_backgroundImg; /*!< Le nom de l'image de fond */
	QGraphicsPixmapItem* m_graphicsBackground; /*!< L'image de fond */
};

#endif
