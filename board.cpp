#include "board.h"

const int Board::defaultMapSize = 7;
const char Board::defaultEmptyCharacter = '_';
const char Board::defaultP1Character = 'X';
const char Board::defaultP2Character = 'O';

using namespace std;

Board::Board(QObject *parent) : QObject(parent) {
	width = 7;
	height = 7;
	p1Character = defaultP1Character;
	p2Character = defaultP2Character;

	boxes = nullptr;
}

void Board::create() {
	boxes = new char*[width];
	for(int i=0; i<width; i++) {
		boxes[i] = new char[height];
	}

	for(int i=0; i<width; i++)
		for(int j=0; j<height; j++)
			boxes[i][j] = defaultEmptyCharacter;
}

bool Board::exists() const {
	return boxes ? true : false;
}

void Board::display() const {
	cout << "  ";
	for(int i=1; i<width+1; i++)
		cout << i << " ";
	cout << endl;

	cout << " +";
	for(int i=1; i<width+1; i++) {
		cout << "--";
	}
	cout << "+" << endl;
}

QPair<int, int> Board::getMapSize() const {
	return QPair<int, int>(width, height);
}

char Board::getP1Character() const {
	return p1Character;
}

char Board::getP2Character() const {
	return p2Character;
}
