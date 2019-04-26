#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <iostream>
#include <QTextStream>
#include <QStringList>
#include <QMap>
#include <QDir>
#include <QDebug>

class Translator {
public:
	Translator(QString languageFolder);

	void setLang(QString lang);
	QString qTranslate(const char* string, bool replaceSpecialChars = false);
	std::string stdTranslate(const char* string);

	const QStringList getAvailableLanguages(bool consoleMode = false) const;
	static QString replaceSpecialChars(const QString& str);

private:
	bool loadLang();

	static const QString defaultLanguage;

	QDir languageFolder;
	QMap<QString, QString> languagesAvailable;
	QString currentLanguage;

	QMap<QString, QString> translation;
};

#endif // LANGUAGE_H
