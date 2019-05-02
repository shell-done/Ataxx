#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsScene>

class MainMenu : public QGraphicsScene {
	Q_OBJECT

public:
	MainMenu(int width, int height, QObject* parent);
};

#endif // MAINMENU_H
