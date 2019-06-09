#ifndef GRAPHICSPLAYERFRAMEITEM_H
#define GRAPHICSPLAYERFRAMEITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QCursor>
#include <QPen>
#include "src/Core/gamecore.h"

class GraphicsPlayerFrameItem : public QObject, public QGraphicsRectItem {
	Q_OBJECT

public:
	GraphicsPlayerFrameItem(GameCore* game, QSize rectSize, int player, char character, int fontSize, QGraphicsItem* parent = nullptr);

	void update();

	void enableScoreDisplay(bool display);
	void setScore(int score);

	void setHoverable(bool hoverable);
	bool selected();
	void setSelected(bool selected);

	void setCharacter(char c);
	char character();

	void setPlayer(int player);
	int player();

protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	static const QString characterSelector;
	static const QString characterHovered;
	static const QString characterSelected;
	static const QString charactersThumbs;

	Textures* m_textures;
	Translator* m_tr;

	QGraphicsPixmapItem* m_graphicsFrame;
	QGraphicsPixmapItem* m_graphicsCharacter;
	QGraphicsTextItem* m_graphicsText;

	bool m_isHoverable;
	bool m_selected;
	int m_fontSize;

	int m_player;
	char m_character;
	int m_score;

signals:
	void clicked();
};

#endif // GRAPHICSPLAYERFRAMEITEM_H
