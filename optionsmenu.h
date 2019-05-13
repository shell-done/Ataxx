#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include "game.h"

class OptionsMenu : public QGraphicsScene {
	Q_OBJECT

public:
	OptionsMenu(int width, int height, Game* game, QObject* parent);

protected:
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	static const int topTitleY;
	static const int topTextY;
	static const int margin;

	void generateText(QGraphicsTextItem*& item, QString str, int fontSize, QColor color);
	void hCenter(QGraphicsItem* item, int y);
	void alignLeft(QGraphicsItem* item, int x, int y);
	void alignRight(QGraphicsItem* item, int x, int y);
	void displayArrows(QGraphicsItem* item, int margin);

	int mouseHoverText(const QPoint& mousePos);
	int mouseHoverArrow(const QPoint& mousePos);

	void updateTextures();
	void updateText();

	Game* m_game;
	Textures* m_textures;
	Translator* m_tr;

	QGraphicsPixmapItem* m_background;
	QGraphicsPixmapItem* m_selector;
	QGraphicsPixmapItem* m_arrows[2];
	QGraphicsTextItem* m_title;
	QGraphicsTextItem* m_volume[2];
	QGraphicsTextItem* m_language[2];
	QGraphicsTextItem* m_return;

	int m_menuIdx;

public slots:
	void update();
};

#endif // OPTIONSMENU_H
