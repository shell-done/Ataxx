#include "graphicsboarditem.h"

const int GraphicsBoardItem::maxGridSize = 660;

GraphicsBoardItem::GraphicsBoardItem(GameCore* game, QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent), m_game(game) {
	m_texture = m_game->textures();
	m_game->board()->generate();

	m_boxesSize = maxGridSize/game->board()->width();
	m_width = (m_boxesSize - 1)*game->board()->width() + 1;

	m_boxClicked = QPoint(-1, -1);

	initBackground();
	initBoxes();

	updateBoard();
}

GraphicsBoardItem::~GraphicsBoardItem() {
	for(int i=0; i<m_game->board()->width(); i++)
		delete[] m_boxes[i];

	delete[] m_boxes;
}

void GraphicsBoardItem::initBackground() {
	QPixmap pixmap(m_width, m_width);
	QPixmap emptyBox(m_texture->loadPixmap("grid/empty_box.png").scaled(m_boxesSize, m_boxesSize));

	QPainter p(&pixmap);

	int width = m_game->board()->width();
	for(int i=0; i<width; i++) {
		for(int j=0; j<width; j++) {
			QPoint dest(i * (m_boxesSize - 1), j * (m_boxesSize - 1));
			p.drawPixmap(dest, emptyBox);
		}
	}

	setPixmap(pixmap);

	p.end();
}

void GraphicsBoardItem::initBoxes() {
	int width = m_game->board()->width();

	m_boxes = new QGraphicsPixmapItem**[width];
	for(int i=0; i<width; i++)
		m_boxes[i] = new QGraphicsPixmapItem*[width];

	QPixmap transparentPixmap(m_boxesSize - 6, m_boxesSize - 6);
	transparentPixmap.fill(QColor(255, 255, 255, 1));

	for(int i=0; i<width; i++) {
		for(int j=0; j<width; j++) {
			m_boxes[i][j] = new QGraphicsPixmapItem(transparentPixmap, this);
			m_boxes[i][j]->setPos(3 + (m_boxesSize - 1)*i, 3 + (m_boxesSize - 1)*j);
		}
	}
}

void GraphicsBoardItem::updateBoard() {
	QPixmap transparentPixmap(m_boxesSize - 6, m_boxesSize - 6);
	transparentPixmap.fill(QColor(255, 255, 255, 1));

	int width = m_game->board()->width();

	for(int i=0; i<width; i++) {
		for(int j=0;j< width; j++) {
			char character = -1;

			if(m_game->board()->at(QPoint(i, j)) != m_game->board()->emptyBoxCharacter)
				character = m_game->board()->at(QPoint(i, j));

			if(character == -1)
				m_boxes[i][j]->setPixmap(transparentPixmap);
			else
				m_boxes[i][j]->setPixmap(m_texture->loadPixmap(QString("characters/pawns/%1.png").arg(character)).scaled(m_boxesSize - 6, m_boxesSize - 6));

			if(m_game->board()->boxBelongByCurrentPlayer(QPoint(i, j)))
				m_boxes[i][j]->setCursor(Qt::PointingHandCursor);
			else
				m_boxes[i][j]->setCursor(Qt::ArrowCursor);
		}
	}
}

void GraphicsBoardItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	QPoint clickPos = (event->scenePos() - pos()).toPoint();

	for(int i=0; i<m_game->board()->width(); i++)
		for(int j=0; j<m_game->board()->width(); j++)
			if(m_boxes[i][j]->sceneBoundingRect().translated(-pos()).contains(clickPos)) {
				boxClicked(QPoint(i, j));
				return;
			}

	QGraphicsPixmapItem::mousePressEvent(event);
}

void GraphicsBoardItem::boxClicked(QPoint box) {
	if(m_game->board()->boxBelongByCurrentPlayer(box)) {
		if(m_boxClicked.x() == -1 || m_boxClicked == box) {
			displayAllowedBoxes(box);

		} else if(m_game->board()->boxBelongByCurrentPlayer(box)) {
			displayAllowedBoxes(m_boxClicked);
			m_boxClicked = QPoint(-1, -1);
			displayAllowedBoxes(box);

		}

		if(m_boxClicked.x() == -1)
			m_boxClicked = box;
		else
			m_boxClicked = QPoint(-1, -1);

	} else if(m_game->board()->at(box) == m_game->board()->emptyBoxCharacter) {
		movePawn(box);
		m_boxClicked = QPoint(-1, -1);
	}
}

void GraphicsBoardItem::displayAllowedBoxes(QPoint src) {
	QVector<QPoint> boxes = m_game->board()->currentPlayerAllowedMoves(src);

	QCursor newCursor = Qt::ArrowCursor;
	QPixmap newPixmap(m_boxesSize - 6, m_boxesSize - 6);
	newPixmap.fill(QColor(255, 255, 255, 1));

	if(m_boxClicked.x() == -1) {
		QPainter painter(&newPixmap);
		painter.setOpacity(0.4);
		painter.drawPixmap(0, 0, m_texture->loadPixmap(QString("characters/pawns/%1.png").arg(m_game->board()->currentPlayer())).scaled(m_boxesSize - 6, m_boxesSize - 6));
		painter.end();

		newCursor = Qt::PointingHandCursor;
	}

	for(const QPoint& b : boxes) {
		m_boxes[b.x()][b.y()]->setCursor(newCursor);
		m_boxes[b.x()][b.y()]->setPixmap(newPixmap);
	}
}

void GraphicsBoardItem::movePawn(QPoint dest) {
	if(!m_game->board()->currentPlayerAllowedMove(m_boxClicked, dest))
		return;

	m_game->board()->playMove(m_boxClicked, dest);
	m_game->update();

	emit pawnMoved();
}
