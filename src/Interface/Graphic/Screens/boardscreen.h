#ifndef BOARDSCREEN_H
#define BOARDSCREEN_H

/*!
 * \file boardscreen.h
 * \brief Fichier de la classe BoardScreen
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QGraphicsItemGroup>
#include <QTimer>
#include <QTextDocument>
#include <QMediaPlayer>
#include "screen.h"
#include "src/Interface/Graphic/Items/graphicsbuttonitem.h"
#include "src/Interface/Graphic/Items/graphicsplayerframeitem.h"
#include "src/Interface/Graphic/Items/graphicsboarditem.h"


/*!
 * \class BoardScreen boardscreen.h
 * \brief Classe représentant l'écran de jeu
 *
 * La classe affiche la grille, les joueurs, le joueur actuel, un timer et 2 boutons pour quitter ou recommencer
 */
class BoardScreen : public Screen {
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
	BoardScreen(int width, int height, GameCore* game, QObject* parent);

private:
	/*!
	 * \brief Place les items sur la scène
	*/
	void placeItems();

	GraphicsBoardItem* m_graphicsBoardItem; /*!< Le plateau de jeu */

	GraphicsPlayerFrameItem* m_graphicsPlayerFrames[4]; /*!< Les 4 potentiels joueurs */
	QGraphicsTextItem* m_graphicsTimer; /*!< Le timer affiché */

	GraphicsPlayerFrameItem* m_graphicsCurrentPlayerFrame; /*!< Le joueur actuel */
	QGraphicsTextItem* m_graphicsCurrentPlayerText; /*!< Le texte du joueur actuel */
	GraphicsButtonItem* m_buttons[2]; /*!< Les bouttons quitter et recommencer */

	QTimer* m_timer; /*!< Le timer */
	int m_minutes; /*!< Le nombre de minutes écoulées depuis le début de cette partie */
	int m_seconds; /*!< Le nombre de secondes écoulées depuis le début de cette partie */

	QMediaPlayer* m_soundPlayer; /*!< Le player pour les effets de son */

public slots:
	/*!
	 * \brief Génère les items pouvant changer à chaque partie (grille et nombre de joueurs)
	*/
	void generateBoard();

	/*!
	 * \brief Met à jour l'item
	*/
	void update();

private slots:
	/*!
	 * \brief Ajoute une seconde au timer
	*/
	void addSecondToTimer();

	/*!
	 * \brief Déplace un pion
	 *
	 * S'occupe de finir la partie et d'afficher le gagnant si besoin
	*/
	void pawnMoved();

	/*!
	 * \brief Reset le plateau et le timer
	*/
	void restart();

	/*!
	 * \brief Renvoie au menu principal
	*/
	void quit();
};

#endif // BOARDSCREEN_H
