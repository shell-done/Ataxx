#include "characterselectionscreen.h"

const int CharacterSelectionScreen::topTitleY = 30;
const int CharacterSelectionScreen::topTextY = 140;
const int CharacterSelectionScreen::margin = 330;

CharacterSelectionScreen::CharacterSelectionScreen(int width, int height, GameCore* game, QObject* parent) : Screen(width, height, game, "menus/character_selection_menu.png", parent) {
	m_title = nullptr;

	for(int i=0; i<4; i++)
		m_playersGroup[i] = nullptr;

	for(int i=0; i<20; i++)
		m_thumbsGroup[i] = nullptr;

	m_grid = nullptr;

	m_buttons[0] = new GraphicsButtonItem(game, "menus/half_selector.png", "graphic:menu:global:return", 40);
	m_buttons[1] = new GraphicsButtonItem(game, "menus/half_selector.png", "graphic:menu:global:next", 40);
	addItem(m_buttons[0]);
	addItem(m_buttons[1]);

	connect(m_buttons[0], SIGNAL(clicked()), this, SLOT(back()));
	connect(m_buttons[1], SIGNAL(clicked()), this, SLOT(next()));

	m_playersDisplayed = 0;
	m_playerSelected = 0;

	updateTextures();
	updateText();
}

void CharacterSelectionScreen::updateTextures() {
	QVector<char> playersChar = m_game->board()->playersList();

	if(m_playersDisplayed != playersChar.size()) {
		for(int i=0; i<m_playersDisplayed; i++) {
			disconnect(m_playersGroup[i], SIGNAL(clicked()), this, SLOT(characterClicked()));
			removeItem(m_playersGroup[i]);
			delete m_playersGroup[i];
			m_playersGroup[i] = nullptr;
		}

		m_playersDisplayed = playersChar.size();

		for(int i=0; i<playersChar.size(); i++) {
			m_playersGroup[i] = new GraphicsPlayerFrameItem(m_game, QSize(192, 192), i+1, playersChar[i], 30);
			m_playersGroup[i]->setHoverable(true);
			connect(m_playersGroup[i], SIGNAL(clicked()), this, SLOT(characterClicked()));
			addItem(m_playersGroup[i]);
		}

		m_playersGroup[0]->setSelected(true);
		m_playerSelected = 0;
	}

	createThumbsGroup();
	displayGroups();
}

void CharacterSelectionScreen::updateText() {
	generateText(m_title, "graphic:local:character:title", 60, m_textures->primaryColor());
	hCenter(m_title, topTitleY);

	alignLeft(m_buttons[0], 330, static_cast<int>(height() - 50 - m_buttons[0]->boundingRect().height()));
	alignRight(m_buttons[1], 330, static_cast<int>(height() - 50 - m_buttons[1]->boundingRect().height()));
}

void CharacterSelectionScreen::update() {
	updateTextures();
	updateText();

	for(int i=0; i<2; i++)
		m_buttons[i]->update();

	for(int i=0; i<4; i++)
		if(m_playersGroup[i])
			m_playersGroup[i]->update();

	Screen::update();
}

void CharacterSelectionScreen::createThumbsGroup() {
	QVector<char> playersChar = m_game->board()->playersList();

	if(m_grid) {
		removeItem(m_grid);

		for(QGraphicsItem* group : m_grid->childItems()) {
			for(QGraphicsItem* item : group->childItems())
				delete item;

			delete group;
		}

		delete m_grid;
	}

	m_grid = createItemGroup(QList<QGraphicsItem*>());

	for(int i=0; i<20; i++) {
		QGraphicsPixmapItem* icon = addPixmap(m_textures->loadPixmap(QString("characters/pawns/%1.png").arg(static_cast<char>('A' + i))));
		icon->setPos(3, 3);

		QGraphicsPixmapItem* box;
		bool selected = false;
		for(char c : playersChar) {
			if(i == c - 'A')
				selected = true;
		}

		if(selected)
			box = addPixmap(m_textures->loadPixmap("menus/pawn_selected.png"));
		else
			box = addPixmap(m_textures->loadPixmap("menus/pawn_selector.png"));

		m_thumbsGroup[i] = createItemGroup(QList<QGraphicsItem*>() << icon << box);

		int x = i%5;
		int y = i/5;
		m_thumbsGroup[i]->setPos(m_thumbsGroup[i]->boundingRect().width()*x - 3*x, m_thumbsGroup[i]->boundingRect().height()*y - 3*y);

		if(selected)
			m_thumbsGroup[i]->setZValue(1);

		m_grid->addToGroup(m_thumbsGroup[i]);
	}
}

void CharacterSelectionScreen::displayGroups() {
	for(int i=0; i<4; i++) {
		if(!m_playersGroup[i])
			continue;

		if(i == 0) alignLeft(m_playersGroup[i], 130, topTextY);
		else if(i == 1) alignRight(m_playersGroup[i], 130, topTextY);
		else if(i == 2) alignLeft(m_playersGroup[i], 130, topTextY + 220);
		else if(i == 3) alignRight(m_playersGroup[i], 130, topTextY + 220);
	}

	hCenter(m_grid, 175);
}

int CharacterSelectionScreen::mouseOverThumb(const QPoint &mousePos) {
	for(int i=0; i<20; i++)
		if(m_thumbsGroup[i]->boundingRect().translated(m_thumbsGroup[i]->pos() + m_grid->pos()).contains(mousePos))
			return i;

	return -1;
}

void CharacterSelectionScreen::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	QGraphicsScene::mouseMoveEvent(event);
	int thumbHovered = mouseOverThumb(event->scenePos().toPoint());

	QVector<char> thumbsSelected = m_game->board()->playersList();

	for(int i=0; i<m_grid->childItems().size(); i++) {
		if(!thumbsSelected.contains(static_cast<char>('A' + i))) {
			static_cast<QGraphicsPixmapItem*>(m_thumbsGroup[i]->childItems()[1])->setPixmap(m_textures->loadPixmap("menus/pawn_selector.png"));
			static_cast<QGraphicsItemGroup*>(m_thumbsGroup[i])->setZValue(0);
		}
	}

	if(thumbHovered == -1)
		return;

	if(!thumbsSelected.contains(static_cast<char>('A' + thumbHovered))) {
		static_cast<QGraphicsPixmapItem*>(m_thumbsGroup[thumbHovered]->childItems()[1])->setPixmap(m_textures->loadPixmap("menus/pawn_selected.png"));
		static_cast<QGraphicsItemGroup*>(m_thumbsGroup[thumbHovered])->setZValue(1);
	}
}

void CharacterSelectionScreen::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	QGraphicsScene::mousePressEvent(event);

	int thumbHovered = mouseOverThumb(event->scenePos().toPoint());
	if(thumbHovered == -1)
		return;

	QVector<char> thumbsSelected = m_game->board()->playersList();

	if(thumbsSelected.contains(static_cast<char>('A' + thumbHovered)))
		return;

	m_game->board()->setPlayerChar(m_playerSelected, static_cast<char>(thumbHovered + 'A'));
	m_playersGroup[m_playerSelected]->setCharacter(static_cast<char>(thumbHovered + 'A'));

	update();

	mouseMoveEvent(event);
}

void CharacterSelectionScreen::back() {
	m_game->setGameStatus(LOCAL_OPTIONS);
}

void CharacterSelectionScreen::next() {
	m_game->setGameStatus(LOCAL_IN_GAME);
}

void CharacterSelectionScreen::characterClicked() {
	GraphicsPlayerFrameItem* frameItem = static_cast<GraphicsPlayerFrameItem*>(sender());
	m_playerSelected = frameItem->player() - 1;

	for(int i=0; i<m_playersDisplayed; i++)
		if(i != m_playerSelected)
			m_playersGroup[i]->setSelected(false);
}
