#include "translator.h"

using namespace std;

const QString Translator::defaultLanguage = "English";

Translator::Translator(QString langFolder) : m_languageFolder(langFolder) {
	m_currentLanguage = "";
	QStringList langFilesFound = m_languageFolder.entryList(QStringList() << "*.lang", QDir::Files);

	for(const QString& filePath: langFilesFound) {
		QFile file(m_languageFolder.path() + "/" + filePath);

		if(file.open(QIODevice::ReadOnly)) {
		   QTextStream in(&file);
		   QString lang = in.readLine();

		   m_languagesAvailable.insert(lang, filePath);

		   file.close();
		}
	}

	if(m_languagesAvailable.isEmpty()) {
		m_currentLanguage = "";
		cerr << "[WARNING] No lang files found" << endl;
		return;
	}

	if(m_languagesAvailable.keys().contains(defaultLanguage)) {
		m_currentLanguage = defaultLanguage;
	} else {
		m_currentLanguage = m_languagesAvailable.firstKey();
	}

	if(!loadLang()) {
		m_currentLanguage = "";
		QString error = "[WARNING] Can't read language file : " + m_currentLanguage;
		cerr << error.toStdString() << endl;
	}
}

bool Translator::loadLang() {
	QFile langFile(m_languageFolder.path() + "/" + m_languagesAvailable[m_currentLanguage]);

	if (langFile.open(QIODevice::ReadOnly)) {
		m_translations.clear();

		QTextStream in(&langFile);
		in.readLine();
		while (!in.atEnd()) {
			QString line = in.readLine();

			QStringList data = line.split(" = ");

			if(data.size() != 2)
				continue;

			m_translations.insert(data[0], data[1]);
		}

		langFile.close();
		return true;
	}

	return false;
}


void Translator::setLang(QString lang) {
	QString prevLang = m_currentLanguage;

	if(m_languagesAvailable.keys().contains(lang)) {
		m_currentLanguage = lang;
	} else {
		cerr << QString("[WARNING] Language : %1 does not exists").arg(replaceSpecialChars(lang)).toStdString() << endl;

		if(m_languagesAvailable.keys().contains(defaultLanguage)) {
			m_currentLanguage = defaultLanguage;
		} else if(!m_languagesAvailable.isEmpty()) {
			m_currentLanguage = m_languagesAvailable.firstKey();
			cerr << "[WARNING] Default language not found" << endl;
		} else {
			cerr << "[WARNING] No languages found" << endl;
			return;
		}
	}

	if(!loadLang()) {
		m_currentLanguage = prevLang;
		cerr << QString("[WARNING] Can't read language file : %1").arg(lang).toStdString() << endl;
	} else {
		cout << QString("%1 %2").arg(qTranslate("console:options:languageSet", true)).arg(replaceSpecialChars(m_currentLanguage)).toStdString() << endl;
	}
}

QString Translator::qTranslate(const char* string, bool replaceSpeChars) {
	QString res = m_translations.value(QString(string), "");

	if(res.isEmpty())
		res = QString(string);

	if(replaceSpeChars)
		res = replaceSpecialChars(res);

	return res;
}

QString Translator::qTranslate(const QString &string, bool replaceSpecialChars) {
	return qTranslate(string.toStdString().c_str(), replaceSpecialChars);
}

std::string Translator::stdTranslate(const char *string) {
	QString qstr = qTranslate(string);
	if(qstr == "")
		return "";

	qstr = replaceSpecialChars(qstr);

	return qstr.toStdString();
}

const QStringList Translator::getAvailableLanguages(bool consoleMode) const {
	QStringList list = m_languagesAvailable.keys();

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
