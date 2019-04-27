#include "board.h"

const char Board::emptyBoxCharacter = ' ';
const char Board::P1Character = 'X';
const char Board::P2Character = 'O';

using namespace std;

Board::Board() : m_width(7), m_height(7), m_boxes(nullptr) {

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

int Board::width() {
	return m_width;
}

void Board::setWidth(int w) {
	if(w >= 5 && w <= 15)
		m_width = w;
	else
		cerr << "[WARNING] Cannot set width to " << w << ". Width must be between 5 and 15" << endl;
}

void Board::setHeigh(int h) {
	if(h >= 5 && h <= 15)
		m_height = h;
	else
		cerr << "[WARNING] Cannot set height to " << h << ". Height must be between 5 and 15" << endl;
}
