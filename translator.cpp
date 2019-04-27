#include "translator.h"

using namespace std;

const QString Translator::defaultLanguage = "English";

Translator::Translator(QString langFolder) : languageFolder(langFolder) {
	currentLanguage = "";
	QStringList langFilesFound = languageFolder.entryList(QStringList() << "*.lang", QDir::Files);

	for(const QString& filePath: langFilesFound) {
		QFile file(languageFolder.path() + "/" + filePath);

		if(file.open(QIODevice::ReadOnly)) {
		   QTextStream in(&file);
		   QString lang = in.readLine();

		   languagesAvailable.insert(lang, filePath);

		   file.close();
		}
	}

	if(languagesAvailable.isEmpty()) {
		currentLanguage = "";
		cerr << "[WARNING] No lang files found" << endl;
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
		cerr << error.toStdString() << endl;
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

			if(data.size() != 2)
				continue;

			translation.insert(data[0], data[1]);
		}

		langFile.close();
		return true;
	}

	return false;
}


void Translator::setLang(QString lang) {
	QString prevLang = currentLanguage;

	if(languagesAvailable.keys().contains(lang)) {
		currentLanguage = lang;
	} else {
		cerr << QString("[WARNING] Language : %1 does not exists").arg(replaceSpecialChars(lang)).toStdString() << endl;

		if(languagesAvailable.keys().contains(defaultLanguage)) {
			currentLanguage = defaultLanguage;
		} else if(!languagesAvailable.isEmpty()) {
			currentLanguage = languagesAvailable.firstKey();
			cerr << "[WARNING] Default language not found" << endl;
		} else {
			cerr << "[WARNING] No languages found" << endl;
			return;
		}
	}

	if(!loadLang()) {
		currentLanguage = prevLang;
		cerr << QString("[WARNING] Can't read language file : %1").arg(lang).toStdString() << endl;
	} else {
		cout << QString("%1 %2").arg(qTranslate("console:options:languageSet", true)).arg(replaceSpecialChars(currentLanguage)).toStdString() << endl;
	}
}

QString Translator::qTranslate(const char* string, bool replaceSpeChars) {
	QString res = translation.value(QString(string), "");

	if(res.isEmpty())
		res = QString(string);

	if(replaceSpeChars)
		res = replaceSpecialChars(res);

	return res;
}

std::string Translator::stdTranslate(const char *string) {
	QString qstr = qTranslate(string);
	if(qstr == "")
		return "";

	qstr = replaceSpecialChars(qstr);

	return qstr.toStdString();
}

const QStringList Translator::getAvailableLanguages(bool consoleMode) const {
	QStringList list = languagesAvailable.keys();

	if(consoleMode)
		for(QString& str: list)
			str = replaceSpecialChars(str);

	return list;
}

QString Translator::replaceSpecialChars(const QString& str) {
	QString copy = str;

	copy.replace(QRegExp(QString::fromUtf8("[éèëê]")), "e");
	copy.replace(QRegExp(QString::fromUtf8("[à]")), "a");
	copy.replace(QRegExp(QString::fromUtf8("[îï]")), "i");
	copy.replace(QRegExp(QString::fromUtf8("[ô]")), "o");
	copy.replace(QRegExp(QString::fromUtf8("[ù]")), "u");
	copy.replace(QRegExp(QString::fromUtf8("[ç]")), "c");

	return copy;
}
