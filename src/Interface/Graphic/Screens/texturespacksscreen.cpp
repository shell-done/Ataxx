#include "texturespacksscreen.h"

const int TexturesPacksScreen::topTitleY = 220;
const int TexturesPacksScreen::topTextY = 330;
const int TexturesPacksScreen::margin = 335;

TexturesPacksScreen::TexturesPacksScreen(int width, int height, GameCore* game, QObject* parent) : Screen(width, height, game, "menus/main_menu.png", parent) {
	m_title = nullptr;
	m_packSelected = nullptr;

	m_arrows[0] = nullptr;
	m_arrows[1] = nullptr;

	//Initialise le bouton
	m_return = new GraphicsButtonItem(game, "menus/selector.png", "graphic:menu:global:return", 40);
	addItem(m_return);
	connect(m_return, SIGNAL(clicked()), this, SLOT(back()));

	m_packIdx = 0;

	updateTextures();
	updateText();
}

void TexturesPacksScreen::updateTextures() {
	//Met à jour les textures
	if(m_packSelected) { // Si le pack n'a pas encore été chargé alors on instancie toutes les images
		m_packSelected->setPixmap(m_textures->loadPixmap("menus/pack_selected.png"));
		m_arrows[0]->setPixmap(m_textures->loadRotatedPixmap("menus/arrow.png", 0));
		alignRight(m_arrows[0], margin, topTextY);
		m_arrows[1]->setPixmap(m_textures->loadRotatedPixmap("menus/arrow.png", 180));
		alignRight(m_arrows[1], margin, topTextY + 175);
	} else { // Sinon on met seulement à jour les images
		m_packSelected = addPixmap(m_textures->loadPixmap("menus/pack_selected.png"));
		m_arrows[0] = addPixmap(m_textures->loadRotatedPixmap("menus/arrow.png", 0));
		m_arrows[1] = addPixmap(m_textures->loadRotatedPixmap("menus/arrow.png", 180));

		for(int i=0; i<2; i++)
			m_arrows[i]->setCursor(Qt::PointingHandCursor);
	}

	m_return->update();

	createPackItems();
	displayPackItems();
}

void TexturesPacksScreen::updateText() {
	//Mise à jour du texte
	generateText(m_title, "graphic:menu:textures:title", 50, m_textures->primaryColor());
	hCenter(m_title, topTitleY);

	hCenter(m_return, static_cast<int>(height() - 50 - m_return->boundingRect().height()));
}

void TexturesPacksScreen::update() {
	updateTextures();
	updateText();

	Screen::update();
}

void TexturesPacksScreen::createPackItems() {
	while(!m_packs.isEmpty()) {
		QGraphicsItemGroup* group = m_packs.takeFirst();
		removeItem(group);
		delete group;
	}

	QList<s_textures_pack> list = m_textures->getPackList();

	for(const s_textures_pack& pack : list) {
		//Création des packs avec le nom, la description et l'icon
		QGraphicsPixmapItem* icon = addPixmap(QPixmap::fromImage(pack.icon).scaled(96, 96));
		QGraphicsTextItem* title = nullptr;
		QGraphicsTextItem* description = nullptr;

		QGraphicsRectItem* boundingRect = addRect(QRect(-5, -5, static_cast<int>(width()) - 2*margin - 70, 102));
		boundingRect->setPen(QPen(Qt::transparent));

		// On place correctement les items
		generateText(title, pack.name.left(15), 30, m_textures->primaryColor());
		generateText(description, pack.description.left(29) + QString("..."), 20, m_textures->tertiaryColor());

		title->setPos(icon->boundingRect().width() + 15, 3);
		description->setPos(icon->boundingRect().width() + 15, 45);

		QGraphicsItemGroup* group = createItemGroup(QList<QGraphicsItem*>() << icon << title << description << boundingRect);
		m_packs.push_front(group);

		group->setVisible(false);
		group->setCursor(Qt::PointingHandCursor);
	}
}

void TexturesPacksScreen::displayPackItems() {
	//On affiche les packs
	for(QGraphicsItemGroup*& group : m_packs)
		group->setVisible(false);

	m_packSelected->setVisible(false);

	for(int i=0; i<2; i++) { // En fonction du défilement
		if(i + m_packIdx >= m_packs.size())
			continue;

		if(i + m_packIdx == m_textures->currentTexturePackIdx()) {
			m_packSelected->setVisible(true);
			alignLeft(m_packSelected, margin, topTextY + 130*i);
		}


		alignLeft(m_packs[i + m_packIdx], margin, topTextY + 130*i);
		m_packs[i + m_packIdx]->setVisible(true);
	}

	if(m_packs.size() < 3) { // S'il y a moins de 3 packs, on n'affiche pas les flèches
		m_arrows[0]->hide();
		m_arrows[1]->hide();
	} else {
		m_arrows[0]->show();
		m_arrows[1]->show();
	}
}

int TexturesPacksScreen::mouseOverText(const QPoint& mousePos) {
	//Texte survolé par la souris
	for(int i=m_packIdx; i<m_packs.size() && i<=m_packIdx+1; i++) {
		if(m_packs[i]->childrenBoundingRect().translated(m_packs[i]->pos()).contains(mousePos))
			return i;
	}

	return -1;
}

int TexturesPacksScreen::mouseOverArrow(const QPoint &mousePos) {
	//Flèche survolée par la souris
	for(int i=0; i<2; i++)
		if(m_arrows[i]->boundingRect().translated(m_arrows[i]->pos()).contains(mousePos))
			return i;

	return -1;
}

void TexturesPacksScreen::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	QGraphicsScene::mouseMoveEvent(event);

	//Si on est au dessus de la flèche, on change la couleur
	int arrowIdx = mouseOverArrow(event->scenePos().toPoint());
	for(int i=0; i<=1; i++)
		if(i == arrowIdx)
			m_arrows[i]->setPixmap(m_textures->loadRotatedPixmap("menus/arrow_onHover.png", 180*i));
		else
			m_arrows[i]->setPixmap(m_textures->loadRotatedPixmap("menus/arrow.png", 180*i));

	//Item pour le pack
	for(int i=0; i<m_packs.size(); i++)
		static_cast<QGraphicsTextItem*>(m_packs[i]->childItems()[1])->setDefaultTextColor(m_textures->primaryColor());


	int idx = mouseOverText(event->scenePos().toPoint());
	if(idx == -1)
		return;

	if(idx != -1)
		static_cast<QGraphicsTextItem*>(m_packs[idx]->childItems()[1])->setDefaultTextColor(m_textures->secondaryColor());
}

void TexturesPacksScreen::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	QGraphicsScene::mousePressEvent(event);

	int idx = mouseOverText(event->scenePos().toPoint());
	int arrowIdx = mouseOverArrow(event->scenePos().toPoint());

	if(idx == -1 && arrowIdx == -1)
		return;

	if(idx != -1) {
		// Si on click sur un pack, on utile se pack
		m_textures->setTexturePackIdx(idx);
	}
	else if(arrowIdx != -1) {
		//Si on click sur une flèche, on change le défilement des packs
		if(arrowIdx == 0 && m_packIdx != 0)
			m_packIdx--;
		else if(arrowIdx == 1 && m_packIdx < m_packs.size() - 2)
			m_packIdx++;

		displayPackItems();
	}

	mouseMoveEvent(event);
}

void TexturesPacksScreen::back() {
	//Retour au menu principal
	m_game->setGameStatus(ON_MAIN_MENU);
}
