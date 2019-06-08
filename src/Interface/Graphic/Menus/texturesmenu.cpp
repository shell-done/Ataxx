#include "texturesmenu.h"

const int TexturesMenu::topTitleY = 210;
const int TexturesMenu::topTextY = 330;
const int TexturesMenu::margin = 335;

TexturesMenu::TexturesMenu(int width, int height, GameCore* game, QObject* parent) : Menu(width, height, game, parent){
	m_background = nullptr;
	m_selector = nullptr;
	m_title = nullptr;
	m_return = nullptr;
	m_packSelected = nullptr;

	m_arrows[0] = nullptr;
	m_arrows[1] = nullptr;

	m_packIdx = 0;

	updateTextures();
	updateText();
}

void TexturesMenu::updateTextures() {
	if(m_background) {
		m_background->setPixmap(m_textures->loadPixmap("menus/main_menu.png"));
		m_selector->setPixmap(m_textures->loadPixmap("menus/selector.png"));
		m_packSelected->setPixmap(m_textures->loadPixmap("menus/pack_selected.png"));
		m_arrows[0]->setPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 0));
		alignRight(m_arrows[0], margin, topTextY);
		m_arrows[1]->setPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 180));
		alignRight(m_arrows[1], margin, topTextY + 175);
	} else {
		m_background = addPixmap(m_textures->loadPixmap("menus/main_menu.png"));
		m_selector = addPixmap(m_textures->loadPixmap("menus/selector.png"));
		m_packSelected = addPixmap(m_textures->loadPixmap("menus/pack_selected.png"));
		m_arrows[0] = addPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 0));
		m_arrows[1] = addPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 180));
	}

	m_selector->hide();

	createPackItems();
	displayPackItems();
}

void TexturesMenu::updateText() {
	generateText(m_title, "graphic:menu:textures:title", 60, m_textures->primaryColor());
	hCenter(m_title, topTitleY);

	generateText(m_return, "graphic:menu:global:return", 50, m_textures->primaryColor());
	hCenter(m_return, topTextY + static_cast<int>(75*3.5));

	hCenter(m_selector, static_cast<int>(m_return->pos().y() + qAbs(m_return->boundingRect().height() - m_selector->boundingRect().height())/2));
}

void TexturesMenu::update() {
	updateTextures();
	updateText();
}

void TexturesMenu::createPackItems() {
	while(!m_packs.isEmpty()) {
		QGraphicsItemGroup* group = m_packs.takeFirst();
		removeItem(group);
		delete group;
	}

	QList<s_textures_pack> list = m_textures->getPackList();

	for(const s_textures_pack& pack : list) {
		QGraphicsPixmapItem* icon = addPixmap(QPixmap::fromImage(pack.icon).scaled(96, 96));
		QGraphicsTextItem* title = nullptr;
		QGraphicsTextItem* description = nullptr;

		QGraphicsRectItem* boundingRect = addRect(QRect(-5, -5, static_cast<int>(width()) - 2*margin - 70, 102));
		boundingRect->setPen(QPen(Qt::transparent));

		generateText(title, pack.name.left(15), 35, m_textures->primaryColor());
		generateText(description, pack.description.left(29) + QString("..."), 20, m_textures->tertiaryColor());

		title->setPos(icon->boundingRect().width() + 15, 3);
		description->setPos(icon->boundingRect().width() + 15, 45);

		QGraphicsItemGroup* group = createItemGroup(QList<QGraphicsItem*>() << icon << title << description << boundingRect);
		m_packs.push_front(group);

		group->setVisible(false);
	}
}

void TexturesMenu::displayPackItems() {
	for(QGraphicsItemGroup*& group : m_packs)
		group->setVisible(false);

	m_packSelected->setVisible(false);

	for(int i=0; i<2; i++) {
		if(i + m_packIdx >= m_packs.size())
			continue;

		if(i + m_packIdx == m_textures->currentTexturePackIdx()) {
			m_packSelected->setVisible(true);
			alignLeft(m_packSelected, margin, topTextY + 130*i);
		}


		alignLeft(m_packs[i + m_packIdx], margin, topTextY + 130*i);
		m_packs[i + m_packIdx]->setVisible(true);
	}
}

int TexturesMenu::mouseHoverText(const QPoint& mousePos) {
	if(m_selector->boundingRect().translated(m_selector->pos()).contains(mousePos))
		return -1;

	for(int i=m_packIdx; i<m_packs.size() && i<=m_packIdx+1; i++) {
		if(m_packs[i]->childrenBoundingRect().translated(m_packs[i]->pos()).contains(mousePos))
			return i;
	}

	return -2;
}

int TexturesMenu::mouseHoverArrow(const QPoint &mousePos) {
	for(int i=0; i<2; i++)
		if(m_arrows[i]->boundingRect().translated(m_arrows[i]->pos()).contains(mousePos))
			return i;

	return -1;
}

void TexturesMenu::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	int arrowIdx = mouseHoverArrow(event->scenePos().toPoint());
	for(int i=0; i<=1; i++)
		if(i == arrowIdx)
			m_arrows[i]->setPixmap(m_textures->loadRotatePixmap("menus/arrow_hovered.png", 180*i));
		else
			m_arrows[i]->setPixmap(m_textures->loadRotatePixmap("menus/arrow.png", 180*i));

	int idx = mouseHoverText(event->scenePos().toPoint());
	if(idx == -2 || m_menuIdx == idx)
		return;

	m_menuIdx = idx;

	m_selector->hide();
	m_return->setDefaultTextColor(m_textures->primaryColor());
	for(int i=0; i<m_packs.size(); i++)
		static_cast<QGraphicsTextItem*>(m_packs[i]->childItems()[1])->setDefaultTextColor(m_textures->primaryColor());

	if(idx == -1) {
		m_return->setDefaultTextColor(m_textures->secondaryColor());
		m_selector->show();
	} else {
		static_cast<QGraphicsTextItem*>(m_packs[idx]->childItems()[1])->setDefaultTextColor(m_textures->secondaryColor());
	}
}

void TexturesMenu::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	int idx = mouseHoverText(event->scenePos().toPoint());
	int arrowIdx = mouseHoverArrow(event->scenePos().toPoint());

	if(idx == -2 && arrowIdx == -1)
		return;

	if(idx != -2) {
		m_menuIdx = idx;
		if(idx == -1)
			m_game->setGameStatus(ON_MAIN_MENU);
		else {
			m_textures->setTexturePackIdx(idx);
		}
	}

	if(arrowIdx != -1) {
		if(arrowIdx == 0 && m_packIdx != 0)
			m_packIdx--;
		else if(arrowIdx == 1 && m_packIdx < m_packs.size() - 2)
			m_packIdx++;

		displayPackItems();
	}

	mouseMoveEvent(event);
}
