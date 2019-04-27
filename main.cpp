#include <QApplication>
#include "game.h"
#include "console.h"

int main(int argc, char** argv) {
	QMap<QString, QString> arguments;
	arguments["mode"] = "console";

	arguments = readArguments(argc, argv, arguments);

	Game* game = new Game(arguments);
	Console* console = new Console(game);

	game->update();

	Q_UNUSED(console);

	return 0;
}
