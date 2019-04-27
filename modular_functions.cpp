#include "core.h"

QMap<QString, QString> readArguments(int argc, char** argv, QMap<QString, QString> arguments) {
	for(int i=0; i<argc - 1; i++) {
		QString qarg(argv[i]);

		if(qarg.size() == 0)
			continue;

		if(qarg[0] != "-")
			continue;

		qarg = qarg.remove("-");

		arguments[qarg] = argv[i+1];
	}

	return arguments;
}
