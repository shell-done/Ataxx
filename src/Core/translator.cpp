#include "translator.h"

using namespace std;

const QString Translator::defaultLanguage = "English";

Translator::Translator(QString langFolder) : m_languageFolder(langFolder) {
	m_useDefault = false;
	m_currentLanguage = ""; // Initialise les variables
	QStringList langFilesFound = m_languageFolder.entryList(QStringList() << "*.lang", QDir::Files); // Liste les fichiers .lang

	for(const QString& filePath: langFilesFound) {
		QFile file(m_languageFolder.path() + "/" + filePath); // Lit chaque fichier

		if(file.open(QIODevice::ReadOnly)) {
		   QTextStream in(&file);
		   QString lang = in.readLine(); // Ajoute le nom de la langue et son chemin dans la liste des langues disponibles

		   m_languagesAvailable.insert(lang, filePath);

		   file.close();
		}
	}

	if(m_languagesAvailable.isEmpty()) {
		//Si aucun fichier de langue n'est trouvé, on affiche une erreur et on charge la langue du fichier .qrc
		m_currentLanguage = "";
		cerr << "[WARNING] No lang files found in " << m_languageFolder.path().toStdString() << "/ folder. Using the default language (english)"<< endl;
		cerr << "[WARNING] Please consider adding language files in the right folder (probably the build folder) then restart the game" << endl;
		cerr << "[WARNING] Please read the readme.md file to get more information" << endl;

		cerr << endl;
		m_useDefault = true;
		loadLang(true);

		return;
	}

	if(m_languagesAvailable.keys().contains(defaultLanguage)) { // Si la langue par défaut a été trouvée, on charge celle-ci
		m_currentLanguage = defaultLanguage;
	} else {
		m_currentLanguage = m_languagesAvailable.firstKey(); // Sinon on charge la première trouvée
	}

	if(!loadLang()) {
		//En cas de problème lors du chargement de la langue, on charge la langue du fichier .qrc et on affiche une erreur
		m_currentLanguage = "";
		QString error = "[WARNING] Can't read language file : " + m_currentLanguage;
		cerr << error.toStdString() << endl;
		loadLang(true);
	}
}

bool Translator::loadLang(bool defaultLang) {
	QFile langFile;

	if(defaultLang) // Si defaultLang vaut true, on charge la langue du fichier .qrc
		langFile.setFileName(":resources/default_en.lang");
	else
		langFile.setFileName(m_languageFolder.path() + "/" + m_languagesAvailable[m_currentLanguage]);

	if (langFile.open(QIODevice::ReadOnly)) {
		m_translations.clear(); // On enlève toutes les traductions existentes

		QTextStream in(&langFile);
		in.readLine();
		while (!in.atEnd()) {
			QString line = in.readLine();

			QStringList data = line.split(" = "); // On sépare chaque ligne au niveau du '='

			if(data.size() != 2)
				continue;

			m_translations.insert(data[0], data[1]); // Et on insère la traduction
		}

		langFile.close();
		return true;
	}

	return false;
}

QString Translator::currentLanguage(bool useAccents) {
	if(useAccents)
		return m_currentLanguage;

	return replaceSpecialChars(m_currentLanguage);
}

void Translator::setLang(QString lang) {
	QString prevLang = m_currentLanguage;

	if(m_languagesAvailable.keys().contains(lang)) { // On vérifie que la langue demandée existe
		m_currentLanguage = lang;
	} else {
		//Sinon on affiche un message d'erreur
		cerr << QString("[WARNING] Language : %1 does not exists").arg(replaceSpecialChars(lang)).toStdString() << endl;

		//On essaye de charger la langue par défaut, si ce n'est pas possible on essaye de charger la première langue trouvée
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
		//Si on arrive pas à charger la langue, on recharge l'ancienne
		m_currentLanguage = prevLang;
		cerr << QString("[WARNING] Can't read language file : %1").arg(lang).toStdString() << endl;
		loadLang();
	}
}

QString Translator::qTranslate(const char* string, bool replaceSpeChars) {
	QString res = m_translations.value(QString(string), ""); // On passe la chaine en QString et on la traduit

	if(res.isEmpty())
		res = QString(string); // Si le résultat est la chaine nulle, on garde la chaine de départ

	if(replaceSpeChars) // On enlève les caractères spéciaux
		res = replaceSpecialChars(res);

	return res;
}

QString Translator::qTranslate(const QString &string, bool replaceSpecialChars) {
	//Passe la chaine en c string et appelle qTranslate()
	return qTranslate(string.toStdString().c_str(), replaceSpecialChars);
}

std::string Translator::stdTranslate(const char *string) {
	QString qstr = qTranslate(string);
	if(qstr == "")
		return "";

	qstr = replaceSpecialChars(qstr);

	return qstr.toStdString();
}

void Translator::setNextLang() {
	if(availableLanguages().size() < 2) // Si il n'y a qu'une seule langue, on s'arrête
		return;

	//Sinon on passe à la langue suivante
	QString nextLang = availableLanguages()[(availableLanguages().indexOf(m_currentLanguage) + 1)%availableLanguages().size()];
	setLang(nextLang);
}

void Translator::setPrevLang() {
	if(availableLanguages().size() < 2) // Si il n'y a qu'une seule langue, on s'arrête
		return;

	int idx = availableLanguages().indexOf(m_currentLanguage);
	if(idx > 0)
		idx--;
	else
		idx = availableLanguages().size() - 1;

	//Sinon on passe à la langue précédente
	setLang(availableLanguages()[idx]);
}

const QStringList Translator::availableLanguages(bool useAccents) const {
	QStringList list = m_languagesAvailable.keys();

	//On fait la liste des langues disponibles, on remplace les caractères spéciaux au besoin
	if(!useAccents)
		for(QString& str: list)
			str = replaceSpecialChars(str);

	return list;
}

QString Translator::replaceSpecialChars(const QString& str) {
	QString copy = str;

	//Remplace tous les caractères spéciaux (pour l'instant français) dans la chaine
	copy.replace(QRegExp(QString::fromUtf8("[éèëê]")), "e");
	copy.replace(QRegExp(QString::fromUtf8("[à]")), "a");
	copy.replace(QRegExp(QString::fromUtf8("[îï]")), "i");
	copy.replace(QRegExp(QString::fromUtf8("[ô]")), "o");
	copy.replace(QRegExp(QString::fromUtf8("[ù]")), "u");
	copy.replace(QRegExp(QString::fromUtf8("[ç]")), "c");

	return copy;
}
