#include "characterselectionmenu.h"

const int CharacterSelectionMenu::topTitleY = 30;
const int CharacterSelectionMenu::topTextY = 140;
const int CharacterSelectionMenu::margin = 330;

CharacterSelectionMenu::CharacterSelectionMenu(int width, int height, Game* game, QObject* parent) : Menu(width, height, game, parent) {
	m_background = nullptr;
	m_title = nullptr;

	m_return = nullptr;
	m_start = nullptr;

	for(int i=0; i<2; i++)
		m_textBox[i] = nullptr;

	for(int i=0; i<4; i++)
		m_playersGroup[i] = nullptr;

	for(int i=0; i<20; i++)
		m_thumbsGroup[i] = nullptr;

	m_grid = nullptr;

	updateTextures();
	updateText();
}

void CharacterSelectionMenu::updateTextures() {
	if(m_background) {
		m_background->setPixmap(m_textures->loadPixmap("menus/character_selection_menu.png"));
		m_selector->setPixmap(m_textures->loadPixmap("menus/half_selector.png"));
		m_textBox[0]->setRect(m_selector->boundingRect());
		m_textBox[1]->setRect(m_selector->boundingRect());
	} else {
		m_background = addPixmap(m_textures->loadPixmap("menus/character_selection_menu.png"));
		m_selector = addPixmap(m_textures->loadPixmap("menus/half_selector.png"));
		m_textBox[0] = addRect(m_selector->boundingRect());
		m_textBox[1] = addRect(m_selector->boundingRect());
	}

	for(int i=0; i<2; i++)
		m_textBox[i]->setPen(QPen(Qt::transparent));

	m_selector->hide();

	createPlayersGroup();
	createThumbsGroup();
	displayGroups();
}

void CharacterSelectionMenu::updateText() {
	generateText(m_title, "graphic:local:character:title", 60, m_textures->primaryColor());
	hCenter(m_title, topTitleY);

	generateText(m_return, "graphic:menu:global:return", 50, m_textures->primaryColor());
	alignLeft(m_return, margin + 25, 601);
	adjustRectangles(m_textBox[0], m_return);

	generateText(m_start, "graphic:menu:global:next", 50, m_textures->primaryColor());
	alignRight(m_start, margin + 25, 601);
	adjustRectangles(m_textBox[1], m_start);
}

void CharacterSelectionMenu::createPlayersGroup() {
	for(int i=0; i<4; i++)
		if(m_playersGroup[i]) {
			QGraphicsItem* item = m_playersGroup[i];
			removeItem(item);
			delete item;

			m_playersGroup[i] = nullptr;
		}

	QVector<char> playersChar = m_game->board()->playersList();

	for(int i=0; i<m_game->board()->playersNumber(); i++) {
		QGraphicsPixmapItem* icon = addPixmap(m_textures->loadPixmap(QString("characters/large/%1.png").arg(playersChar[i] - 'A')));
		icon->setPos(4, 4);

		QGraphicsPixmapItem* box;
		if(i == m_menuIdx)
			box = addPixmap(m_textures->loadPixmap("menus/char_selection_selector_selected.png"));
		else
			box = addPixmap(m_textures->loadPixmap("menus/char_selection_selector.png"));

		QGraphicsTextItem* playerName = addText(m_tr->qTranslate("graphic:local:character:name", m_textures->useAccents()).arg(i+1));
		playerName->setFont(m_textures->loadFont(30));

		if(i == m_menuIdx)
			playerName->setDefaultTextColor(m_textures->secondaryColor());
		else
			playerName->setDefaultTextColor(m_textures->primaryColor());

		adjustRectangles(playerName, box);
		playerName->setY(box->boundingRect().height() - playerName->boundingRect().height() - 5);

		m_playersGroup[i] = createItemGroup(QList<QGraphicsItem*>() << icon << box << playerName);
	}
}

void CharacterSelectionMenu::createThumbsGroup() {
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
		QGraphicsPixmapItem* icon = addPixmap(m_textures->loadPixmap(QString("characters/thumbnails/%1.png").arg(i)));
		icon->setPos(3, 3);

		QGraphicsPixmapItem* box;
		bool selected = false;
		for(char c : playersChar) {
			if(i == c - 'A')
				selected = true;
		}

		if(selected)
			box = addPixmap(m_textures->loadPixmap("menus/char_selection_thumb_selector_selected.png"));
		else
			box = addPixmap(m_textures->loadPixmap("menus/char_selection_thumb_selector.png"));

		m_thumbsGroup[i] = createItemGroup(QList<QGraphicsItem*>() << icon << box);

		int x = i%5;
		int y = i/5;
		m_thumbsGroup[i]->setPos(m_thumbsGroup[i]->boundingRect().width()*x - 3*x, m_thumbsGroup[i]->boundingRect().height()*y - 3*y);

		if(selected)
			m_thumbsGroup[i]->setZValue(1);

		m_grid->addToGroup(m_thumbsGroup[i]);
	}
}

void CharacterSelectionMenu::displayGroups() {
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

void CharacterSelectionMenu::update() {
	updateTextures();
	updateText();
}

QPair<int, int> CharacterSelectionMenu::mouseOverElement(const QPoint &mousePos) {
	for(int i=0; i<2; i++)
		if(m_textBox[i]->boundingRect().translated(m_textBox[i]->pos()).contains(mousePos))
			return {0, i};

	for(int i=0; i<4; i++)
		if(m_playersGroup[i])
			if(m_playersGroup[i]->boundingRect().translated(m_playersGroup[i]->pos()).contains(mousePos))
				return {1, i};

	for(int i=0; i<20; i++)
		if(m_thumbsGroup[i]->boundingRect().translated(m_thumbsGroup[i]->pos() + m_grid->pos()).contains(mousePos)) {
			return {2, i};
		}

	return {-1, 0};
}

void CharacterSelectionMenu::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	QPair<int, int> el = mouseOverElement(event->scenePos().toPoint());

	QVector<int> thumbsSelected;
	for(char c : m_game->board()->playersList())
		thumbsSelected << c - 'A';

	if(el.first != 1) {
		for(int i=0; i<4; i++)
			if(m_playersGroup[i] && i != m_menuIdx) {
				static_cast<QGraphicsPixmapItem*>(m_playersGroup[i]->childItems()[1])->setPixmap(m_textures->loadPixmap("menus/char_selection_selector.png"));
				static_cast<QGraphicsTextItem*>(m_playersGroup[i]->childItems()[2])->setDefaultTextColor(m_textures->primaryColor());
			}

		for(int i=0; i<m_grid->childItems().size(); i++) {
			if(!thumbsSelected.contains(i)) {
				static_cast<QGraphicsPixmapItem*>(m_thumbsGroup[i]->childItems()[1])->setPixmap(m_textures->loadPixmap("menus/char_selection_thumb_selector.png"));
				static_cast<QGraphicsItemGroup*>(m_thumbsGroup[i])->setZValue(0);
			}
		}

	}

	if(el.first == -1)
		return;

	m_elementHover = el;
	m_selector->hide();
	m_start->setDefaultTextColor(m_textures->primaryColor());
	m_return->setDefaultTextColor(m_textures->primaryColor());

	if(el.first == 0) {
		if(el.second == 0) {
			m_return->setDefaultTextColor(m_textures->secondaryColor());
			m_selector->setPos(m_textBox[0]->pos());
		} else {
			m_start->setDefaultTextColor(m_textures->secondaryColor());
			m_selector->setPos(m_textBox[1]->pos());
		}

		m_selector->show();

	} else if(el.first == 1 && el.second != m_menuIdx) {
		static_cast<QGraphicsPixmapItem*>(m_playersGroup[el.second]->childItems()[1])->setPixmap(m_textures->loadPixmap("menus/char_selection_selector_hover.png"));
		static_cast<QGraphicsTextItem*>(m_playersGroup[el.second]->childItems()[2])->setDefaultTextColor(m_textures->secondaryColor());

	} else if(el.first == 2 && !thumbsSelected.contains(el.second)) {
		static_cast<QGraphicsPixmapItem*>(m_thumbsGroup[el.second]->childItems()[1])->setPixmap(m_textures->loadPixmap("menus/char_selection_thumb_selector_selected.png"));
		static_cast<QGraphicsItemGroup*>(m_thumbsGroup[el.second])->setZValue(1);
	}
}

void CharacterSelectionMenu::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	QPair<int, int> el = mouseOverElement(event->scenePos().toPoint());
	if(el.first == -1)
		return;

	m_elementHover = el;
	if(el.first == 0) {
		if(el.second == 0) {
			m_game->setGameStatus(LOCAL_OPTIONS);
			m_menuIdx = 0;
		}

	} else if(el.first == 1) {
		static_cast<QGraphicsPixmapItem*>(m_playersGroup[m_menuIdx]->childItems()[1])->setPixmap(m_textures->loadPixmap("menus/char_selection_selector.png"));
		static_cast<QGraphicsTextItem*>(m_playersGroup[m_menuIdx]->childItems()[2])->setDefaultTextColor(m_textures->primaryColor());

		m_menuIdx = el.second;
		static_cast<QGraphicsPixmapItem*>(m_playersGroup[el.second]->childItems()[1])->setPixmap(m_textures->loadPixmap("menus/char_selection_selector_selected.png"));

	} else if(el.first == 2) {
		QVector<int> thumbsSelected;
		for(char c : m_game->board()->playersList())
			thumbsSelected << c - 'A';

		if(thumbsSelected.contains(el.second))
			return;

		m_game->board()->setPlayerChar(m_menuIdx, static_cast<char>(el.second + 'A'));

		update();
	}

	mouseMoveEvent(event);
}
