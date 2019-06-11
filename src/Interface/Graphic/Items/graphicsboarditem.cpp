#include "graphicsboarditem.h"

const int GraphicsBoardItem::maxGridSize = 660;

GraphicsBoardItem::GraphicsBoardItem(GameCore* game, QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent), m_game(game) {
	m_texture = m_game->textures();
	m_game->board()->generate();

	m_boxesSize = maxGridSize/game->board()->width(); // Largeur d'une case de la grille
	m_width = (m_boxesSize - 1)*game->board()->width() + 1; // Largeur de la grille

	m_blocked = false;
	m_boxClicked = QPoint(-1, -1); // Initialisation des variables

	initBackground();
	initBoxes();

	updateBoard();
}

GraphicsBoardItem::~GraphicsBoardItem() {
	//On désalloue tout
	for(int i=0; i<m_game->board()->width(); i++)
		delete[] m_boxes[i];

	delete[] m_boxes;
}

void GraphicsBoardItem::initBackground() {
	QPixmap pixmap(m_width, m_width);
	QPixmap emptyBox(m_texture->loadPixmap("grid/empty_box.png").scaled(m_boxesSize, m_boxesSize));

	QPainter p(&pixmap);

	//On recoubre l'image de fond de plusieurs copies de l'image de la case vide
	int width = m_game->board()->width();
	for(int i=0; i<width; i++) {
		for(int j=0; j<width; j++) {
			QPoint dest(i * (m_boxesSize - 1), j * (m_boxesSize - 1));
			p.drawPixmap(dest, emptyBox);
		}
	}

	//Et on applique l'image de fons
	setPixmap(pixmap);

	p.end();
}

void GraphicsBoardItem::initBoxes() {
	int width = m_game->board()->width();

	//On alloue dynamiquement un tableau de pointeur sur chaque case du tableau
	m_boxes = new QGraphicsPixmapItem**[width];
	for(int i=0; i<width; i++)
		m_boxes[i] = new QGraphicsPixmapItem*[width];

	QPixmap transparentPixmap(m_boxesSize - 6, m_boxesSize - 6);
	transparentPixmap.fill(Qt::transparent);

	for(int i=0; i<width; i++) {
		for(int j=0; j<width; j++) { // ajoute un item de type QPixmap invisible dans chaque case
			m_boxes[i][j] = new QGraphicsPixmapItem(transparentPixmap, this);

			//On place correctement l'item pour qu'il soit centré dans la case
			m_boxes[i][j]->setPos(3 + (m_boxesSize - 1)*i, 3 + (m_boxesSize - 1)*j);
		}
	}
}

void GraphicsBoardItem::updateBoard() {
	QPixmap transparentPixmap(m_boxesSize - 6, m_boxesSize - 6);
	transparentPixmap.fill(Qt::transparent);

	int width = m_game->board()->width();

	//Pour chauqe case du tableau
	for(int i=0; i<width; i++) {
		for(int j=0;j< width; j++) {
			char character = -1;

			//Si la case n'est pas vide, on récupère le caractère de la case
			if(m_game->board()->at(QPoint(i, j)) != m_game->board()->emptyBoxCharacter)
				character = m_game->board()->at(QPoint(i, j));

			if(character == -1) // Si celui-ci vaut -1 on dessine une case vide
				m_boxes[i][j]->setPixmap(transparentPixmap);
			else if(character == '-') // Si c'est un mur
				m_boxes[i][j]->setPixmap(m_texture->loadPixmap(QString("grid/wall_box.png")).scaled(m_boxesSize - 6, m_boxesSize - 6));
			else // Sinon c'est un pion
				m_boxes[i][j]->setPixmap(m_texture->loadPixmap(QString("characters/pawns/%1.png").arg(character)).scaled(m_boxesSize - 6, m_boxesSize - 6));

			// Si le pion appartient au joueur courant, on affiche le curseur
			if(m_game->board()->boxBelongByCurrentPlayer(QPoint(i, j)) && !m_blocked)
				m_boxes[i][j]->setCursor(Qt::PointingHandCursor);
			else
				m_boxes[i][j]->setCursor(Qt::ArrowCursor);
		}
	}
}

void GraphicsBoardItem::block(bool b) {
	m_blocked = b;
}

void GraphicsBoardItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	QPoint clickPos = (event->scenePos() - pos()).toPoint();

	//On cherche quelle case a été cliquée et on appelle la méthode correspondante
	for(int i=0; i<m_game->board()->width(); i++)
		for(int j=0; j<m_game->board()->width(); j++)
			if(m_boxes[i][j]->sceneBoundingRect().translated(-pos()).contains(clickPos)) {
				boxClicked(QPoint(i, j));
				return;
			}

	QGraphicsPixmapItem::mousePressEvent(event);
}

void GraphicsBoardItem::boxClicked(QPoint box) {
	if(m_blocked) // Si la grille est bloqué on ne fait rien
		return;

	if(m_game->board()->boxBelongByCurrentPlayer(box)) {
		if(m_boxClicked.x() == -1 || m_boxClicked == box) {
			displayAllowedBoxes(box); // S'il s'agit de la première case cliquée ou de la case déjà cliquée, on affiche/cache les aides

		} else if(m_game->board()->boxBelongByCurrentPlayer(box)) {
			//S'il s'agit d'une autre case qui appartient au joueur
			displayAllowedBoxes(m_boxClicked); // On cache l'aide
			m_boxClicked = QPoint(-1, -1);
			displayAllowedBoxes(box); // Et on rapelle l'aide

		}

		if(m_boxClicked.x() == -1) // Si le joueur n'a cliqué sur aucune case auparavant, on définit celle-ci comme la précédente
			m_boxClicked = box;
		else // S'il a déjà cliquée sur celle-ci, on supprime la précédente
			m_boxClicked = QPoint(-1, -1);

	} else if(m_game->board()->currentPlayerAllowedMove(m_boxClicked, box)) { // Si le mouvement entre la case précédente et celle-ci est valide
		//On bouge le pion
		movePawn(box);
		m_boxClicked = QPoint(-1, -1);
	}
}

void GraphicsBoardItem::displayAllowedBoxes(QPoint src) {
	QVector<QPoint> boxes = m_game->board()->currentPlayerAllowedMoves(src);

	QCursor newCursor = Qt::ArrowCursor;
	QPixmap newPixmap(m_boxesSize - 6, m_boxesSize - 6);
	newPixmap.fill(Qt::transparent);

	//On affiche en semi-transparent les aides
	if(m_boxClicked.x() == -1) {
		QPainter painter(&newPixmap);
		painter.setOpacity(0.4);
		painter.drawPixmap(0, 0, m_texture->loadPixmap(QString("characters/pawns/%1.png").arg(m_game->board()->currentPlayer())).scaled(m_boxesSize - 6, m_boxesSize - 6));
		painter.end();

		newCursor = Qt::PointingHandCursor;
	}

	//Er on définie les curseurs
	for(const QPoint& b : boxes) {
		m_boxes[b.x()][b.y()]->setCursor(newCursor);
		m_boxes[b.x()][b.y()]->setPixmap(newPixmap);
	}
}

void GraphicsBoardItem::movePawn(QPoint dest) {
	//Si le mouvement est permis
	if(!m_game->board()->currentPlayerAllowedMove(m_boxClicked, dest))
		return;

	//On le joue, on met à jour le jeu et on émet un signal
	m_game->board()->playMove(m_boxClicked, dest);
	m_game->update();

	emit pawnMoved();
}
