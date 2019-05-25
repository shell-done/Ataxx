#include "board.h"

const char Board::emptyBoxCharacter = ' ';
const char Board::P1Character = 'X';
const char Board::P2Character = 'O';

using namespace std;

Board::Board() : m_width(7), m_height(7), m_round(1), m_boxes(nullptr) {
	m_currentPlayer = P1Character;

	m_playersList << P1Character << P2Character;
}

void Board::generate() {
	m_boxes = new char*[m_width];
	for(int i=0; i<m_width; i++)
		m_boxes[i] = new char[m_height];

	for(int i=0; i<m_width; i++)
		for(int j=0; j<m_height; j++)
			m_boxes[i][j] = emptyBoxCharacter;

	placePawns();
}

void Board::placePawns() {
	QVector<char> pawns;
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
	for(int i=0; i<m_width; i++)
		delete[] m_boxes[i];
	delete[] m_boxes;

	m_boxes = nullptr;
	m_round = 1;
	m_currentPlayer = m_playersList[0];
}

bool Board::exists() {
	return m_boxes ? true : false;
}

char** Board::boxes() const {
	return m_boxes;
}

int Board::width() {
	return m_width;
}

void Board::setWidth(int w) {
	if(w >= 5 && w <= 15)
		m_width = w;
	else
		cerr << "[WARNING] Cannot set width to " << w << ". Width must be between 5 and 15" << endl;
}

int Board::height() {
	return m_height;
}

void Board::setHeigh(int h) {
	if(h >= 5 && h <= 15)
		m_height = h;
	else
		cerr << "[WARNING] Cannot set height to " << h << ". Height must be between 5 and 15" << endl;
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
	Q_ASSERT(onGrid(p));

	return m_boxes[p.x()][p.y()];
}

void Board::setCharacter(const QPoint &p, char character) {
	Q_ASSERT(onGrid(p));

	m_boxes[p.x()][p.y()] = character;
}

QVector<QPoint> Board::movesAllowed(const QPoint& src) {
	QVector<QPoint> allowedDest;

	if(at(src) != m_currentPlayer)
		return allowedDest;

	for(int i=-2; i<=2; i++)
		for(int j=-2; j<=2; j++) {
			QPoint dest = src + QPoint(i, j);

			if(moveAllowed(src, dest))
				allowedDest << dest;
		}

	return allowedDest;
}

QPair<QPoint, QPoint> Board::strToPoints(const QStringList& coordinates) {
	bool ok = true;
	if(coordinates.size() != 4)
		ok = false;

	for(int i=0; i<coordinates.size() && ok; i++) {
		if(i%2 == 0 && (coordinates[i].toInt() - 1 < 0 || coordinates[i].toInt() - 1 >= m_width))
			ok = false;
		else if(i%2 == 1 && (coordinates[i].toInt() - 1 < 0 || coordinates[i].toInt() - 1 >= m_height))
			ok = false;
	}

	if(ok)
		return QPair<QPoint, QPoint>(QPoint(coordinates[0].toInt() - 1, coordinates[1].toInt() - 1), QPoint(coordinates[2].toInt() - 1, coordinates[3].toInt() - 1));

	return QPair<QPoint, QPoint>(QPoint(-1, -1), QPoint(-1, -1));
}

bool Board::moveAllowed(const QPoint &origin, const QPoint &dest) {
	if(!onGrid(origin) || !onGrid(dest))
		return false;

	if(at(origin) != m_currentPlayer)
		return false;

	if(at(dest) != emptyBoxCharacter)
		return false;

	if(pow(origin.x() - dest.x(), 2) + pow(origin.y() - dest.y(), 2) >= 9)
		return false;

	return true;
}

void Board::playMove(const QPoint &origin, const QPoint &dest) {
	Q_ASSERT(moveAllowed(origin, dest));

	if(pow(origin.x() - dest.x(), 2) + pow(origin.y() - dest.y(), 2) >= 4) {
		setCharacter(origin, emptyBoxCharacter);
		setCharacter(dest, m_currentPlayer);
	} else {
		setCharacter(dest, m_currentPlayer);
	}

	for(int i=-1; i<=1; i++)
		for(int j=-1; j<=1; j++) {
			QPoint adjacentBox = QPoint(dest.x() + i, dest.y() + j);
			if(onGrid(adjacentBox))
				if(at(adjacentBox) != m_currentPlayer && at(adjacentBox) != emptyBoxCharacter)
					setCharacter(adjacentBox, m_currentPlayer);
		}

	m_currentPlayer = m_playersList[(m_playersList.indexOf(m_currentPlayer) + 1) % m_playersList.size()];
	m_round++;
}

QMap<char, int> Board::countPawns() {
	QMap<char, int> pawns;

	for(char p : m_playersList)
		pawns[p] = 0;

	for(int i=0; i<m_width; i++)
		for(int j=0; j<m_height; j++) {
			char pawnOnBox = at(QPoint(i,j));
			if(!m_playersList.contains(pawnOnBox))
				continue;

			int currentScore = pawns[pawnOnBox] + 1;
			pawns[pawnOnBox] = currentScore;
		}

	return pawns;
}

bool Board::currentPlayerCanPlay() {
	for(int i=0; i<m_width; i++)
		for(int j=0; j<m_height; j++)
			if(at(QPoint(i, j)) == m_currentPlayer)
				if(!movesAllowed(QPoint(i, j)).isEmpty())
					return true;

	return false;
}

char Board::checkWinner() {
	if(currentPlayerCanPlay())
		return emptyBoxCharacter;

	QMap<char, int> pawns = countPawns();

	char bestChar = m_playersList[0];
	int bestScore = pawns[bestChar];
	for(int i=1; i<m_playersList.size(); i++) {
		if(pawns[m_playersList[i]] > bestScore) {
			bestChar = m_playersList[i];
			bestScore = pawns[m_playersList[i]];
		}
	}

	return bestChar;
}
