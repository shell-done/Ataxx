#ifndef BOARD_H
#define BOARD_H

/*!
 * \file board.h
 * \brief Fichier de la classe Board
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QPoint>
#include <QVector>
#include <QMap>
#include <iostream>
#include <time.h>
#include <cstdlib>


/*!
 * \class Board board.h
 * \brief Classe représentant le tableau de jeu
 *
 * La classe contient le tableau de jeu ainsi que certaines informations comme la taille du plateau ou la liste des joueurs
 */

class Board {
public:
	/*!
	 * \brief Constructeur
	 *
	 * Constructeur de la classe Board
	*/
	Board();

	/*!
	 * \brief Destructeur
	 *
	 * Destructeur de la classe Board
	*/
	~Board();


	/*!
	 * \brief Genère une grille de jeu
	 *
	 * Créer la grille de jeu avec pour taille la largeur et la hauteur spécifiés par setWidth() et setHeight()
	*/
	void generate();

	/*!
	 * \brief Réinitialise la grille de jeu
	 *
	 * Vide toutes les cases. Place aléatoirement des murs si setWalls() a été définie à true.
	*/
	void reset();

	/*!
	 * \brief Place tous les pions
	 *
	 * Place les pions dans la grille, le placement est différent en fonction du nombre de joueur
	*/
	void placePawns();

	/*!
	 * \brief Renvoie true si la grille de jeu existe
	 *
	 * Renvoie true si la grille de jeu a été générée avec la méthode generate(), false sinon
	 *
	 * \return true si le tableau a été généré, false sinon
	*/
	bool exists();

	/*!
	 * \brief Détruis la grille de jeu
	 *
	 * Libère la mémoire alloué pour la grille de jeu
	*/
	void destroy();

	/*!
	 * \brief Le tableau de caractères représentant la grille de jeu
	 *
	 * \return La grille de jeu sous la forme d'un tableau de caractères
	*/
	char** boxes() const;


	/*!
	 * \brief Renvoie la largeur de la grille de jeu (en nombre de cases)
	 *
	 * \return La largeur de la grille de jeu
	*/
	int width();

	/*!
	 * \brief Définie la largeur de la grille de jeu
	 *
	 * \param width La largeur du tableau en nombre de cases, doit être compris entre 5 et 12.
	*/
	void setWidth(int width);

	/*!
	 * \brief Renvoie la hauteur de la grille de jeu (en nombre de cases)
	 *
	 * \return La hauteur de la grille de jeu
	*/
	int height();

	/*!
	 * \brief Définie la hauteur de la grille de jeu (en nombre de cases)
	 *
	 * \param height La hauteur du tableau en nombre de cases, doit être compris entre 5 et 12
	*/
	void setHeight(int height);

	/*!
	 * \brief Renvoie la liste des joueurs
	 *
	 * \return Un QVector de caractères représentant la liste des joueurs
	*/
	QVector<char> playersList();

	/*!
	 * \brief Définie la liste des joueurs
	 *
	 * \param players Un QVector de caractères représentant la liste des joueurs (doit contenir entre 2 et 4 caractères)
	*/
	void setPlayersList(QVector<char> players);

	/*!
	 * \brief Définie le caractère représentant un joueur
	 *
	 * \param playerIdx L'index du caractère à remplacer dans la liste des joueurs
	 * \param character Le nouveau caractère représentant le joueur
	*/
	void setPlayerChar(int playerIdx, char character);

	/*!
	 * \brief Renvoie le nombre de joueurs
	 *
	 * \return Le nombre de joueur (compris entre 2 et 4 inclus)
	*/
	int playersNumber();

	/*!
	 * \brief Renvoie un booléen spécifiant si des murs sont générés ou non
	 *
	 * \return true si des murs sont générés avec la map, false sinon
	*/
	bool walls();

	/*!
	 * \brief Définie l'information spécifiant si des murs sont générés ou non
	 *
	 * \param walls Si walls vaut true, alors des murs seront générés
	*/
	void setWalls(bool walls);

	/*!
	 * \brief Renvoie le nombre de coups joués depuis le début de la partie
	 *
	 * \return Un entier correspondant au nombre de coups joués
	*/
	int round();

	/*!
	 * \brief Renvoie le caractère correspondant au joueur actuel
	 *
	 * \return Le caractère correspondant au joueur actuel
	*/
	char currentPlayer();


	/*!
	 * \brief Renvoie un booléeen spécifiant si le point passé en paramètre représente bien une case dans le tableau
	 *
	 * \param point Le point a vérifier
	 * \return true si le point est dans le tableau, false sinon
	*/
	bool onGrid(const QPoint& point);

	/*!
	 * \brief Renvoie le caractère de la case représentée par le point passé en paramètre
	 *
	 * \param point Le point a vérifier
	 * \return Le caractère de la case représentée par le point
	*/
	char at(const QPoint& point);

	/*!
	 * \brief Place le caractère dans le tableau à la case représentée par le point
	 *
	 * \param point Les coordonnées de la case dans le tableau
	 * \param character Le caractère à ajouter au tableau
	*/
	void setCharacter(const QPoint& point, char character);

	/*!
	 * \brief Vérifie si la case représentée par le point passé en paramètre appartient au joueur courant
	 *
	 * \param point Le point a vérifier
	 * \return true si la case appartient au joueur courant, false sinon
	*/
	bool boxBelongByCurrentPlayer(const QPoint& point);


	/*!
	 * \brief Transforme une liste de QString de la forme "1 2 3 4" en une paire de coordonnée (1, 2);(3, 4)
	 *
	 * Si la conversion n'est pas possible, les deux points retournés auront -1 pour valeur x et y
	 *
	 * \param coordinates Une QStringList représentant la liste des coordonnées sous forme de QString
	 * \return Une paire de QPoint avec les coordonnées associés
	*/
	QPair<QPoint, QPoint> strToPoints(const QStringList& coordinates);

	/*!
	 * \brief Vérifie si un joueur peut bien faire un mouvement
	 *
	 * \param origin Le point de départ du pion
	 * \param dest Le point d'arrivé du pion
	 * \param player Le caractère représentant le joueur
	 * \return true si le mouvement est possible, false sinon
	*/
	bool allowedMove(const QPoint& origin, const QPoint& dest, char player);

	/*!
	 * \brief Vérifie si le joueur courant peut bien faire un mouvement
	 *
	 * \param origin Le point de départ du pion
	 * \param dest Le point d'arrivé du pion
	 * \param player Le caractère représentant le joueur courant
	 * \return true si le mouvement est possible, false sinon
	*/
	bool currentPlayerAllowedMove(const QPoint& origin, const QPoint& dest);

	/*!
	 * \brief Renvoie la liste des cases accessibles par un joueur depuis l'un de ses pions
	 *
	 * \param origin Le point de départ du pion
	 * \param char Le caractère représentant le joueur
	 * \return Un vecteur de points représentants toutes les cases d'arrivée possibles
	*/
	QVector<QPoint> allowedMoves(const QPoint& src, char player);

	/*!
	 * \brief Renvoie la liste des cases accessibles par le joueur courant depuis l'un de ses pions
	 *
	 * \param origin Le point de départ du pion
	 * \return Un vecteur de points représentants toutes les cases d'arrivée possibles
	*/
	QVector<QPoint> currentPlayerAllowedMoves(const QPoint& src);

	/*!
	 * \brief Joue le mouvement d'une case à une autre
	 *
	 * Si le mouvement est réalisé dans l'une des cases adjacente (diagonales comprises) alors un pion du joueur est posé dans la case de départ et dans celle d'arrivée
	 * Si le mouvement est réalisé dans l'une des cases adjacentes aux cases précéndetes, le pion est déplacé dans la case d'arrivée et la case de départ devient vide
	 *
	 * \param origin le point représentant la case de départ
	 * \param dest Le caractère représentant la case d'arrivée
	*/
	void playMove(const QPoint& origin, const QPoint& dest);


	/*!
	 * \brief Compte le nombre de pions sur le plateau
	 *
	 * \return Une QMap associant le caractère de chacun des joueurs à son nombre de pion sur le plateau
	*/
	QMap<char, int> countPawns();

	/*!
	 * \brief Vérifie si un joueur peut jouer
	 *
	 * \param player Le caractère du joueur à vérifier
	 * \return true si le joueur peut jouer, false s'il n'a plus de pion ou s'il est bloqué
	*/
	bool playerCanPlay(char player);

	/*!
	 * \brief Vérifie si le joueur courant peut jouer
	 *
	 * \return true si le joueur courant peut jouer, false s'il n'a plus de pion ou s'il est bloqué
	*/
	bool currentPlayerCanPlay();

	/*!
	 * \brief Vérifie si la partie doit s'arrêter
	 *
	 * \return true si au moins 2 joueurs peuvent encore jouer, false sinon
	*/
	bool stopGame();

	/*!
	 * \brief Renvoie le caractère représentant le joueur gagnant (celui ayant le plus de pions sur le plateau)
	 *
	 * \return le caractère du joueur gagnant ou le caractère 'Z' en cas d'égalité
	*/
	char winner();

	static const char emptyBoxCharacter; /*!< Le caractère représentant une case vide*/
	static const char wallCharacter; /*!< Le caractère représentant un mur*/
	static const char P1Character; /*!< Le caractère représentant le joueur 1 par défaut*/
	static const char P2Character; /*!< Le caractère représentant le joueur 2 par défaut*/

private:
	int m_width; /*!< La largeur du plateau */
	int m_height; /*!< La hauteur du plateau */
	bool m_createWalls; /*!< Spécifie si des murs doivent être créés */

	int m_round; /*!< Le nombre de coups joués depuis le début de la partie */
	char m_currentPlayer; /*!< Le caractère représentant le joueur courant */

	QVector<char> m_playersList; /*!< La liste des joueurs */

	char** m_boxes; /*!< Le tableau de caractères représentant le plateau de jeu */
};

#endif // BOARD_H
