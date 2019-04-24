#include "translator.h"

using namespace std;

const QString Translator::defaultLanguage = "English";

Translator::Translator(QString langFolder) : languageFolder(langFolder) {
	QStringList langFilesFound = languageFolder.entryList(QStringList() << "*.lang", QDir::Files);

	for(const QString& filePath: langFilesFound) {
		QFile file(languageFolder.path() + "/" + filePath);

		if(file.open(QIODevice::ReadOnly)) {
		   QTextStream in(&file);
		   QString lang = in.readLine().remove(";");

		   languagesAvailable.insert(lang, filePath);

		   file.close();
		}
	}

	if(languagesAvailable.isEmpty()) {
		currentLanguage = "";
		cout << "[WARNING] No lang files found" << endl;
		return;
	}

	if(languagesAvailable.keys().contains(defaultLanguage)) {
		currentLanguage = defaultLanguage;
	} else {
		currentLanguage = languagesAvailable.firstKey();
	}

	if(!loadLang()) {
		currentLanguage = "";
		QString error = "[WARNING] Can't read language file : " + currentLanguage;
		cout << error.toStdString() << endl;
	}
}

bool Translator::loadLang() {
	QFile langFile(languageFolder.path() + "/" + languagesAvailable[currentLanguage]);

	if (langFile.open(QIODevice::ReadOnly)) {
		translation.clear();

		QTextStream in(&langFile);
		in.readLine();
		while (!in.atEnd()) {
			QString line = in.readLine();

			QStringList data = line.split(" = ");
			translation.insert(data[0], data[1]);
		}

		langFile.close();
		return true;
	}

	return false;
}

void Translator::setLang(QString lang) {
	if(!languagesAvailable.keys().contains(lang)) {
		QString error = "[WARNING] Language : " + lang + " does not exists";
		cout << error.toStdString() << endl;

		return;
	}

	loadLang();
}

QString Translator::qTranslate(const char* string) {
	QString res = translation.value(QString(string), "");

	if(res.isEmpty())
		res = QString(string);

	return res;
}

std::string Translator::stdTranslate(const char *string) {
	std::string res = translation.value(QString(string), "").toStdString();

	if(res == "")
		res = std::string(string);

	return res;
}
