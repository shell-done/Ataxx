#include <QApplication>
#include "src/utils.h"
#include "src/Core/gamecore.h"
#include "src/Interface/Console/console.h"
#include "src/Interface/Graphic/window.h"

int main(int argc, char** argv) {
	QMap<QString, QString> arguments;
	arguments["mode"] = "graphic";

	arguments = readArguments(argc, argv, arguments);

	GameCore* game = new GameCore(arguments);
	Console* console = nullptr;
	Window* window = nullptr;

	Q_UNUSED(console);

	if(game->displayMode() == CONSOLE) {
		console = new Console(game);
		game->update();

		return 0;
	} else if(game->displayMode() == GRAPHIC || game->displayMode() == MIXED) {
		QApplication app(argc, argv);
		game->loadTextures();

		window = new Window(game);
		window->show();

		if(game->displayMode() == MIXED)
			console = new Console(game);

		game->update();

		return app.exec();
	}

	return 0;
}
