#include <QApplication>
#include "game.h"
#include "console.h"
#include "window.h"

#include <iostream>
#include <QPushButton>

int main(int argc, char** argv) {
	QMap<QString, QString> arguments;
	arguments["mode"] = "graphic";

	arguments = readArguments(argc, argv, arguments);

	Game* game = new Game(arguments);
	Console* console = nullptr;
	Window* window = nullptr;

	Q_UNUSED(console);

	if(game->displayMode() == CONSOLE) {
		console = new Console(game);
		game->update();

		return 0;
	} else if(game->displayMode() == GRAPHIC) {
		QApplication app(argc, argv);

		window = new Window(game);
		window->show();

		game->update();

		return app.exec();
	}

	return 0;
}
