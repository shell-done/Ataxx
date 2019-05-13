#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "game.h"

class MainMenu : public QGraphicsScene {
	Q_OBJECT

public:
	MainMenu(int width, int height, Game* game, QObject* parent);

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	static const int topTextY;

	int mouseHoverText(const QPoint& mousePos);

	void updateTextures();
	void updateText();

	Game* m_game;
	Textures* m_textures;
	Translator* m_tr;

	QGraphicsPixmapItem* m_background;
	QGraphicsPixmapItem* m_selector;
	QGraphicsTextItem* m_texts[5];

	int m_menuIdx;

public slots:
	void update();
};

#endif // MAINMENU_H
