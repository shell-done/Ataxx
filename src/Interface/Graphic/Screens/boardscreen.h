#ifndef BOARDSCREEN_H
#define BOARDSCREEN_H

#include <QGraphicsItemGroup>
#include <QTimer>
#include <QTextDocument>
#include <QMediaPlayer>
#include "screen.h"
#include "src/Interface/Graphic/Items/graphicsbuttonitem.h"
#include "src/Interface/Graphic/Items/graphicsplayerframeitem.h"
#include "src/Interface/Graphic/Items/graphicsboarditem.h"

class BoardScreen : public Screen {
	Q_OBJECT

public:
	BoardScreen(int width, int height, GameCore* game, QObject* parent);

private:
	void placeItems();

	GraphicsBoardItem* m_graphicsBoardItem;

	GraphicsPlayerFrameItem* m_graphicsPlayerFrames[4];
	QGraphicsTextItem* m_graphicsTimer;

	GraphicsPlayerFrameItem* m_graphicsCurrentPlayerFrame;
	QGraphicsTextItem* m_graphicsCurrentPlayerText;
	GraphicsButtonItem* m_buttons[2];

	QTimer* m_timer;
	int m_minutes;
	int m_seconds;

	QMediaPlayer* m_soundPlayer;

public slots:
	void generateBoard();
	void update();

private slots:
	void addSecondToTimer();
	void pawnMoved();

	void restart();
	void quit();
};

#endif // BOARDSCREEN_H
