#include "board.h"

const char Board::emptyBoxCharacter = ' ';
const char Board::wallCharacter = '-';
const char Board::P1Character = 'A';
const char Board::P2Character = 'B';

using namespace std;

Board::Board() : m_width(7), m_height(7), m_round(1), m_boxes(nullptr) {
	m_currentPlayer = P1Character;
	m_createWalls = false; //Initialisation des variables
	m_boxes = nullptr;

	m_playersList << P1Character << P2Character; // Ajouts des 2 joueurs par défauts à la liste des joueurs
}

Board::~Board() {
	destroy();
}

void Board::generate() {
	//Alloue dynamiquement un tableau de caractères de taille m_width*m_height
	m_boxes = new char*[m_width];
	for(int i=0; i<m_width; i++)
		m_boxes[i] = new char[m_height];

	reset();
}

void Board::reset() {
	for(int i=0; i<m_width; i++)
		for(int j=0; j<m_height; j++) {
			m_boxes[i][j] = emptyBoxCharacter; // Définie toutes les cases comme étant vides

			if(m_createWalls && rand()%10 == 0) {
				m_boxes[i][j] = wallCharacter; // Si l'option createWalls() est définie à true, alors chaque case à une chance sur 10 d'être un mur
			}
		}

	m_round = 1;
	m_currentPlayer = m_playersList[0]; // Définie le joueur courant au premier joueur de la liste
	placePawns();
}

void Board::placePawns() {
	QVector<char> pawns;

	//Places les pions sur la grille en fonction du nombre de joueurs

	if(m_playersList.size() == 2)
		pawns << m_playersList[0] << m_playersList[1] << m_playersList[1] << m_playersList[0];
	else if(m_playersList.size() == 3)
		pawns << m_playersList[0] << m_playersList[1] << m_playersList[2] << emptyBoxCharacter;
	else
		pawns << m_playersList[0] << m_playersList[1] << m_playersList[2] << m_playersList[3];

	setCharacter(QPoint(0, 0), pawns[0]);
	setCharacter(QPoint(m_width - 1, 0), pawns[1]);
	setCharacter(QPoint(0, m_height - 1), pawns[2]);
	setCharacter(QPoint(m_width - 1, m_height - 1), pawns[3]);
}

void Board::destroy() {
	//Désalloue la grille de jeu précédemment alloué dynamiquement
	for(int i=0; i<m_width; i++)
		delete[] m_boxes[i];
	delete[] m_boxes;

	//Réinitialise certaines variables pour une éventuelle prochaine partie
	m_boxes = nullptr;
	m_round = 1;
	m_currentPlayer = m_playersList[0];
}

bool Board::exists() {
	return m_boxes ? true : false; // Renvoie true si m_boxes n'est pas le pointeur null
}

char** Board::boxes() const {
	return m_boxes; // Renvoie le tableau
}

int Board::width() {
	return m_width;
}

void Board::setWidth(int w) {
	//Définie la largeur de la grille si w est compris entre 5 et 12, sinon un message d'erreur est affiché et la taille de la grille ne bouge pas

	if(w >= 5 && w <= 12)
		m_width = w;
	else
		cerr << "[WARNING] Cannot set width to " << w << ". Width must be between 5 and 12" << endl;
}

int Board::height() {
	return m_height;
}

void Board::setHeight(int h) {
	//Définie la hauteur de la grille si w est compris entre 5 et 12, sinon un message d'erreur est affiché et la taille de la grille ne bouge pas

	if(h >= 5 && h <= 12)
		m_height = h;
	else
		cerr << "[WARNING] Cannot set height to " << h << ". Height must be between 5 and 12" << endl;
}

QVector<char> Board::playersList() {
	return m_playersList;
}

void Board::setPlayersList(QVector<char> players) {
	if(players.size() < 2 || players.size() > 4) {
		cerr << "[WARNING] The number of players must be between 2 and 4" << endl;
		return;
	}

	m_playersList.clear();
	m_playersList = players;
	m_currentPlayer = players[0];
}

void Board::setPlayerChar(int playerIdx, char character) {
	if(m_playersList.contains(character)) {
		cerr << "[WARNING] This character is already selected" << endl;
		return;
	}

	if(playerIdx >= m_playersList.size()) {
		cerr << "[WARNING] Cannot set the charactère of the player " << playerIdx << endl;
		return;
	}

	m_playersList[playerIdx] = character;

	if(playerIdx == 0) // S'il s'agit du premier joueur de la liste, on définir le joueur courant à ce joueur
		m_currentPlayer = m_playersList[playerIdx];
}

int Board::playersNumber() {
	return m_playersList.size();
}

bool Board::walls() {
	return m_createWalls;
}

void Board::setWalls(bool b) {
	m_createWalls = b;
}

int Board::round() {
	return m_round;
}

char Board::currentPlayer() {
	return m_currentPlayer;
}

bool Board::onGrid(const QPoint& p) {
	if(p.x() >= 0 && p.x() < m_width && p.y() >= 0 && p.y() < m_height)
		return true;

	return false;
}

char Board::at(const QPoint& p) {
	Q_ASSERT(onGrid(p)); //On s'assure sur que le point est sur la grille

	return m_boxes[p.x()][p.y()];
}

void Board::setCharacter(const QPoint &p, char character) {
	Q_ASSERT(onGrid(p)); //On s'assure sur que le point est sur la grille

	m_boxes[p.x()][p.y()] = character;
}

bool Board::boxBelongByCurrentPlayer(const QPoint& p) {
	Q_ASSERT(onGrid(p)); //On s'assure sur que le point est sur la grille

	if(at(p) == m_currentPlayer) //Si le joueur courant possède cette case, alors true, sinon false
		return true;

	return false;
}

QPair<QPoint, QPoint> Board::strToPoints(const QStringList& coordinates) {
	bool ok = true;
	if(coordinates.size() != 4) // On vérifie qu'il y a bien 4 chaines de caractères (pour les 4 coordonnées)
		ok = false;

	for(int i=0; i<coordinates.size() && ok; i++) { //On parcours les 4 coordonnées
		if(i%2 == 0 && (coordinates[i].toInt() - 1 < 0 || coordinates[i].toInt() - 1 >= m_width)) // On vérifie que la 1ère et la troisième sont compris entre 0 et la largeur
			ok = false;
		else if(i%2 == 1 && (coordinates[i].toInt() - 1 < 0 || coordinates[i].toInt() - 1 >= m_height))// On vérifie que la 1ère et la troisième sont compris entre 0 et la hauteur
			ok = false;
	} //Si une des conditions est fausse, on passe ok à false

	//Si les coordonnées sont valide, on renvoie la paire de coordoonée, sinon on renvoie une paire de qpoint définie à -1
	if(ok)
		return QPair<QPoint, QPoint>(QPoint(coordinates[0].toInt() - 1, coordinates[1].toInt() - 1), QPoint(coordinates[2].toInt() - 1, coordinates[3].toInt() - 1));

	return QPair<QPoint, QPoint>(QPoint(-1, -1), QPoint(-1, -1));
}

bool Board::allowedMove(const QPoint &origin, const QPoint &dest, char player) {
	if(!onGrid(origin) || !onGrid(dest)) // On vérifie que les points sont sur la grille
		return false;

	if(at(origin) != player) // Que la case de départ appartient bien au joueur
		return false;

	if(at(dest) != emptyBoxCharacter) // Que la case d'arrivée est vide
		return false;

	if(pow(origin.x() - dest.x(), 2) + pow(origin.y() - dest.y(), 2) >= 9) // Et que la distance entre les cases au carré est inférieur à 9
		return false;

	return true;
}

bool Board::currentPlayerAllowedMove(const QPoint &origin, const QPoint &dest) {
	return allowedMove(origin, dest, m_currentPlayer);
}

QVector<QPoint> Board::allowedMoves(const QPoint &src, char player) {
	QVector<QPoint> allowedDest;

	if(at(src) != player)
		return allowedDest;

	for(int i=-2; i<=2; i++)
		for(int j=-2; j<=2; j++) {
			QPoint dest = src + QPoint(i, j);

			if(allowedMove(src, dest, player)) //On regarde toutes les cases de destination possibles pour une case de départ donnée
				allowedDest << dest; // On remplis le vecteur que des cases d'arrivée valide
		}

	return allowedDest;
}

QVector<QPoint> Board::currentPlayerAllowedMoves(const QPoint& src) {
	return allowedMoves(src, m_currentPlayer);
}

void Board::playMove(const QPoint &origin, const QPoint &dest) {
	Q_ASSERT(currentPlayerAllowedMove(origin, dest));

	if(pow(origin.x() - dest.x(), 2) + pow(origin.y() - dest.y(), 2) >= 4) {
		setCharacter(origin, emptyBoxCharacter); // Si on est sur une case à 2 de distance, on vide la case courante et on déplace le pion sur la case d'arrivée
		setCharacter(dest, m_currentPlayer);
	} else {
		setCharacter(dest, m_currentPlayer); // Si on ets sur une case adjacente, on duplique le pion sur la case d'arrivée
	}

	for(int i=-1; i<=1; i++)
		for(int j=-1; j<=1; j++) { // Pour toutes les cases adjacentes
			QPoint adjacentBox = QPoint(dest.x() + i, dest.y() + j);
			if(onGrid(adjacentBox)) // On vérifie qu'elles sont sur la grille
				if(m_playersList.contains(at(adjacentBox)))
					setCharacter(adjacentBox, m_currentPlayer); //On change tous les pions directement autour du pion d'arrivée
		}

	if(!stopGame()) { // Si le jeu peut continuer
		do {
			m_currentPlayer = m_playersList[(m_playersList.indexOf(m_currentPlayer) + 1) % m_playersList.size()]; // On passe au joueur suivant
		} while(!currentPlayerCanPlay()); // Tant que le joueur courant ne peut pas jouer
	}

	m_round++;
}

QMap<char, int> Board::countPawns() {
	QMap<char, int> pawns;

	for(char p : m_playersList)
		pawns[p] = 0; // On met le score de chcun à 0

	for(int i=0; i<m_width; i++)
		for(int j=0; j<m_height; j++) { // Parcours toute la grille
			char pawnOnBox = at(QPoint(i,j));
			if(!m_playersList.contains(pawnOnBox)) // Si le caractère est celui d'un joueur
				continue;

			int currentScore = pawns[pawnOnBox] + 1; // Alors on incrémente le score de ce joueur
			pawns[pawnOnBox] = currentScore;
		}

	return pawns;
}

bool Board::playerCanPlay(char player) {
	for(int i=0; i<m_width; i++)
		for(int j=0; j<m_height; j++)
			if(at(QPoint(i, j)) == player) // Pour chaque pion du joueur
				if(!allowedMoves(QPoint(i, j), player).isEmpty()) // On vérifie qu'il peut faire au moins un mouvement
					return true;

	return false;
}

bool Board::currentPlayerCanPlay() {
	return playerCanPlay(m_currentPlayer);
}

bool Board::stopGame() {
	int playersCanPlay = 0;

	for(char c: m_playersList)
		if(playerCanPlay(c))
			playersCanPlay++; // On compte le nombre de joueur qui peuvent jouer

	if(playersCanPlay < 2) // Si au moins deux joueurs peuvent encore jouer on continue, sinon on arrête le jeu
		return true;

	return false;
}

char Board::winner() {
	QMap<char, int> pawns = countPawns(); // On compte le nombre de pions

	char bestChar = m_playersList[0];
	int bestScore = pawns[bestChar];
	bool tie = false;

	for(int i=1; i<m_playersList.size(); i++) {
		if(pawns[m_playersList[i]] > bestScore) {
			bestChar = m_playersList[i];
			bestScore = pawns[m_playersList[i]]; // On cherche quel est le meilleur score et le meilleur joueur associé
			tie = false;
		} else if(pawns[m_playersList[i]] == bestScore) {
			tie = true; // En cas d'égalité, on met cette variable à true
		}
	}

	if(tie) // En cas d'égalité entre les meilleurs scores, on renvoie le caractère 'Z'
		return 'Z';

	//Sinon on renvoie le caractère représentant le meilleur joueur
	return bestChar;
}
