#include "utils.h"

QMap<QString, QString> readArguments(int argc, char** argv, QMap<QString, QString> arguments) {
	for(int i=0; i<argc - 1; i++) { // On récupère chaque argument sauf le dernier
		QString qarg(argv[i]);

		if(qarg.size() == 0) // Pour éviter d'éventuels problèmes
			continue;

		if(qarg[0] != "-")
			continue;

		//Si l'argument commence par un ou plusieurs tiret, on les enlèves
		qarg = qarg.remove("-");

		//On associe ensuite l'argument dont on a retiré les tiret à l'argument qui le suis
		arguments[qarg] = argv[i+1];
		i++; // On passe l'argument suivant
	}

	//On renvoie la map qui contient les arguments par défauts qui on été éventuellement remplacés et les argument du tableau argv
	return arguments;
}
