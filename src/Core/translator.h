#ifndef LANGUAGE_H
#define LANGUAGE_H

/*!
 * \file translator.h
 * \brief Fichier de la classe Translator
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <iostream>
#include <QTextStream>
#include <QStringList>
#include <QMap>
#include <QDir>

/*!
 * \class Translator translator.h
 * \brief Classe représentant la langue utilisée
 *
 * La classe fournit la liste des langues trouvées ainsi que des méthodes permettant d'accéder aux traductions
 *
 * Pour plus d'informations sur la structure d'un fichier de langue, se reporter au fichier readme.md
 */
class Translator {
public:
	/*!
	 * \brief Constructeur
	 *
	 * \param languageFolder Le dossier contenant les fichiers de langues.
	*/
	Translator(QString languageFolder);


	/*!
	 * \brief Renvoie le nom du langage courant
	 *
	 * \param useAccents Si définie à true, alors le nom de la langue sera renvoyé sans accents
	 * \return Un QString contenant la langue utilisée actuellement
	*/
	QString currentLanguage(bool useAccents = true);

	/*!
	 * \brief Définit la langue actuelle
	 *
	 * \param lang Le nom de la langue à utiliser
	*/
	void setLang(QString lang);

	/*!
	 * \brief Traduit une chaine de caractère C en un QString en utilisant les fichiers de langues
	 *
	 * S'il n'existe aucune traduction, la chaine renvoyée sera identique à la chaine passée en paramètre
	 *
	 * \param string La chaine à traduire
	 * \param useAccents Si définie à true, alors le nom de la langue sera renvoyé sans accents
	 * \return La chaine traduite
	*/
	QString qTranslate(const char* string, bool replaceSpecialChars = false);

	/*!
	 * \brief Traduit une chaine de caractère QString en un QString en utilisant les fichiers de langues
	 *
	 * S'il n'existe aucune traduction, la chaine renvoyée sera identique à la chaine passée en paramètre
	 *
	 * \param string La chaine à traduire
	 * \param useAccents Si définie à true, alors le nom de la langue sera renvoyé sans accents
	 * \return La chaine traduite
	*/
	QString qTranslate(const QString& string, bool replaceSpecialChars = false);

	/*!
	 * \brief Traduit une chaine de caractère C en une chaine de caractère C++ en utilisant les fichiers de langues
	 *
	 * S'il n'existe aucune traduction, la chaine renvoyée sera identique à la chaine passée en paramètre
	 *
	 * \param string La chaine à traduire
	 * \param useAccents Si définie à true, alors le nom de la langue sera renvoyé sans accents
	 * \return La chaine traduite
	*/
	std::string stdTranslate(const char* string);

	/*!
	 * \brief Passe à la langue suivante (ou la première si l'actuelle est la dernière)
	*/
	void setNextLang();

	/*!
	 * \brief Passe à la langue précédente (ou la dernière si l'actuelle est la première)
	*/
	void setPrevLang();

	/*!
	 * \brief Renvoie la liste des langues disponibles
	 *
	 * \param useAccents Si définie à true, alors les noms de la langue seront retournés sans accents
	 * \return La liste des langues disponibles
	*/
	const QStringList availableLanguages(bool useAccents = true) const;

	/*!
	 * \brief Remplace les caractères spéciaux comme les accents d'un QString
	 *
	 * Fonction actuellement disponible uniquement pour le français
	 *
	 * \param str La chaine à traiter
	 * \return Le QString sans accents
	*/
	static QString replaceSpecialChars(const QString& str);

private:
	/*!
	 * \brief Charge les traductions de la langue m_currentLanguage
	 *
	 * Si defaultLang vaut true, alors ce sont les traductions présentes dans le fichier .qrc qui seront utilisées
	 *
	 * \return true si le chargement s'est passé correctement, false sinon
	*/
	bool loadLang(bool defaultLang = false);

	static const QString defaultLanguage; /*!< Langue par défaut */

	bool m_useDefault; /*!< Pour savoir si la langue par défaut (celle du .qrc) est utilisée */
	QDir m_languageFolder; /*!< Dossier contenants les fichiers de langues */
	QMap<QString, QString> m_languagesAvailable; /*!< Liste des langues disponibles */
	QString m_currentLanguage; /*!< Langues actuelle */

	QMap<QString, QString> m_translations; /*!< Map des traductions */
};

#endif // LANGUAGE_H
