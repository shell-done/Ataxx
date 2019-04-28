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
				if(at(adjacentBox) != m_currentPlayer)
					setCharacter(adjacentBox, m_currentPlayer);
		}

	m_currentPlayer = m_playersList[(m_playersList.indexOf(m_currentPlayer) + 1) % m_playersList.size()];
}

char Board::checkWinner() {
	QMap<char, int> pawns;

	for(int i=0; i<m_width; i++)
		for(int j=0; j<m_height; j++) {
			int score = pawns.value(at(QPoint(i, j)), 0);
			score ++;
			pawns[at(QPoint(i, j))] = score;
		}

	for(char pawn : pawns.keys())
		if(!m_playersList.contains(pawn))
			pawns.remove(pawn);

	if(pawns.keys().size() == 1)
		return pawns.key(0);

	return emptyBoxCharacter;
}
