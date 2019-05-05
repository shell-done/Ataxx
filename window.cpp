#include "window.h"

const int Window::m_width = 1280;
const int Window::m_height = 720;

Window::Window(Game* game) : QGraphicsView(), m_game(game) {
	m_mainMenu = new MainMenu(m_width, m_height, game, this);

	setFixedSize(m_width + 2, m_height + 2);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


	setMouseTracking(true);
	setScene(m_mainMenu);

	connect(m_game, SIGNAL(updateWindow()), this, SLOT(gameUpdate()));
}

void Window::gameUpdate() {

}
