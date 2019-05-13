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
	Translator(QString m_languageFolder);

	QString currentLanguage(bool useAccents = true);
	void setLang(QString lang);
	QString qTranslate(const char* string, bool replaceSpecialChars = false);
	QString qTranslate(const QString& string, bool replaceSpecialChars = false);
	std::string stdTranslate(const char* string);
	void setNextLang();
	void setPrevLang();

	const QStringList availableLanguages(bool useAccents = true) const;
	static QString replaceSpecialChars(const QString& str);

private:
	bool loadLang();

	static const QString defaultLanguage;

	QDir m_languageFolder;
	QMap<QString, QString> m_languagesAvailable;
	QString m_currentLanguage;

	QMap<QString, QString> m_translations;
};

#endif // LANGUAGE_H
