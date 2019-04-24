#include "core.h"

std::string translate(QString str) {
	QCoreApplication::tr(str);

	return "a";
}
