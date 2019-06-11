#include "textures.h"

#include <QDebug>

using namespace std;

const QString Textures::defaultTexturesPack = "The Original";

Textures::Textures(QString textFolder, QObject *parent) : QObject(parent), m_texturesFolder(textFolder) {
	m_useDefault = false;
	m_currentTexturesPack = "";
	QStringList texturesList = m_texturesFolder.entryList(QDir::Dirs); //Liste tous les dossiers du dossier de pack de texture

	for(const QString& texturesPackFolder : texturesList) {
		QFile textPackConfigFile(m_texturesFolder.path() + "/" + texturesPackFolder + "/pack.conf"); // On lit le fichier pack.conf de chaque pack

		if(textPackConfigFile.open(QIODevice::ReadOnly)) {
			QTextStream in(&textPackConfigFile);
			QString line = in.readLine();

			QStringList data = line.split(" = ");
			if(data[0] != "pack_name" || data.size() != 2) { // Le nom du pack doit être présent sur la première ligne
				textPackConfigFile.close();
				continue;
			}

			QString packName = data[1];
			if(m_texturesAvailable.keys().contains(packName)) { // Si ce nom de pack est déjà utilisé, on ne garde pas ce pack
				textPackConfigFile.close();
				continue;
			}

			m_texturesAvailable.insert(packName, texturesPackFolder); // On ajoute le pack à la liste

			if(packName == defaultTexturesPack)
				m_currentTexturesPack = packName; // Si le pack de texture par défaut et le nom du pack actuel correspondent, on définit le nom du pack actuel

			line = in.readLine();
			data = line.split(" = ");

			QString description;
			if(data[0] == "description" && data.size() == 2) // On lit et garde la description si celle-ci est fournie
				description = data[1];
			else
				description = "";

			QImage icon(m_texturesFolder.path() + "/" + texturesPackFolder + "/icon.png");
			s_textures_pack pack = {packName, description, icon}; // On charge l'icon et on le place dans la structure
			m_texturesList << pack;

			textPackConfigFile.close();
		}
	}

	if(m_texturesAvailable.isEmpty()) {
		//Si aucun pack n'a été trouvé, on utilise le fichier .qrc et on affiche un message
		m_currentTexturesPack = "";
		cerr << "[WARNING] No textures packs found in " << m_texturesFolder.path().toStdString() << "/ folder. Using default ressources" << endl;
		cerr << "[WARNING] Please consider adding textures packs in the right folder (probably the build folder) then restart the game" << endl;
		cerr << "[WARNING] Please read the readme.md file to get more information" << endl;
		cerr << endl;

		m_useDefault = true;
		loadPack(true);

		return;
	}

	if(m_currentTexturesPack == "") { // Si le pack par défaut n'est pas dans la liste, on prend le premier pack possible
		m_currentTexturesPack = m_texturesAvailable.firstKey();
	}


	if(!loadPack()) { // On essaye de charger le pack, en cas d'échec on affiche une erreur
		m_currentTexturesPack = "";
		QString error = "[WARNING] Can't read textures pack config file : " + m_currentTexturesPack;
		cerr << error.toStdString() << endl;
		loadPack(true);
	}
}

bool Textures::loadPack(bool defaultPack) {
	m_fontName = "";

	//On regarde si un fichier de police est présent
	if(QFile(m_texturesFolder.path() + "/" + m_texturesAvailable[m_currentTexturesPack] + "/font.ttf").exists() || defaultPack) {
		int id = -1; // id du pack de texture chargé

		if(defaultPack)
			id = QFontDatabase::addApplicationFont(":resources/font.ttf"); // Si on utilise le pack par défaut, alors on charge la police par défaut
		else // Sinon, on charge la police du pack
			id = QFontDatabase::addApplicationFont(m_texturesFolder.path() + "/" + m_texturesAvailable[m_currentTexturesPack] + "/font.ttf");

		m_fontName = QFontDatabase::applicationFontFamilies(id).at(0);
	}

	QFile textPackConfigFile;

	if(defaultPack)
		textPackConfigFile.setFileName(":resources/pack.conf"); // Chargement du pack par défaut
	else
		textPackConfigFile.setFileName(m_texturesFolder.path() + "/" + m_texturesAvailable[m_currentTexturesPack] + "/pack.conf");

	if(textPackConfigFile.open(QIODevice::ReadOnly)) { // On lit le ficier de config du pack
		m_description = "No description available";
		m_accents = true;
		m_primaryColor = QColor(255, 255, 255); // On reset les informations
		m_fontName = "";

		QTextStream in(&textPackConfigFile);
		in.readLine();
		while(!in.atEnd()) { // On lit ligne par ligne
			QString line = in.readLine();

			QStringList data = line.split(" = ");

			if(data.size() != 2) // On split les lignes des deux côtés du '=', s'il n'y a pas 2 string disponible alors on passe à la ligne suivante
				continue;

			if(data[0] == "description") // Chargement de la description
				m_description = data[1];

			if(data[0] == "font") {
				if(m_fontName == "") // Si aucun de fichier de police n'est présent mais qu'un nom de police est dans le fichier, on se sert de ce nom
					m_fontName = data[1];
			}

			if(data[0] == "use_accents") {
				if(data[1] == "true")
					m_accents = true; // Activation ou non des accents
				else
					m_accents = false;
			}

			//Chargement des couleurs
			if(data[0] == "primary_color")
				m_primaryColor = loadColor(data[1]);

			if(data[0] == "secondary_color")
				m_secondaryColor = loadColor(data[1]);

			if(data[0] == "tertiary_color")
				m_tertiaryColor = loadColor(data[1]);
		}

		textPackConfigFile.close();
		return true; // Si tout s'est bien passé, on return true
	}

	return false;
}

QColor Textures::loadColor(const QString &str) {
	QColor color;

	QStringList rgb = str.split(","); // On split au niveau des virgules
	if(rgb.size() != 3)
		return Qt::white;

	bool ok;
	bool rgbOk = true;
	int components[3];

	for(int i=0; i<3; i++) {
		components[i] = rgb[i].trimmed().toInt(&ok);
		if(!ok || components[i] < 0 || components[i] > 255)
			rgbOk = false;
	}

	if(rgbOk) // Si le chargement est bon, on return la couleur
		color = QColor(components[0], components[1], components[2]);
	else // Sinon on return du blanc
		color = Qt::white;

	return color;
}

QString Textures::currentTexturePack() const {
	return m_currentTexturesPack;
}

int Textures::currentTexturePackIdx() const {
	for(int i=0; i<m_texturesList.size(); i++)
		if(m_texturesList[i].name == m_currentTexturesPack)
			return m_texturesList.size() - i - 1; // On cherche l'index dupack de texture actuel

	return -1;
}

void Textures::setTexturePack(QString& name) {
	if(!m_texturesAvailable.keys().contains(name)) {
		cerr << "[WARNING] Unknown pack : " << name.toStdString() << endl; // On vérifie que le nom du pack existe
		return;
	}

	QString prevPack = m_currentTexturesPack; // On garde le nom de l'ancien pack utilisé
	m_currentTexturesPack = name;


	if(!loadPack()) { // Si le chargement du nouveau pack échoue, on recharge l'ancien
		cerr << "[WARNING] Error while loading pack : " << name.toStdString() << endl;
		m_currentTexturesPack = prevPack;
		loadPack();
	}

	//On demande à recharger les textures
	emit updateTextures();
}

void Textures::setTexturePackIdx(int idx) {
	if(idx < 0 || idx >= m_texturesList.size()) {
		cerr << "[WARNING] Textures pack index out of range" << endl;
		return;
	}

	if(idx == currentTexturePackIdx())
		return;

	setTexturePack(m_texturesList[m_texturesList.size() - idx - 1].name);
}

QList<s_textures_pack> Textures::getPackList() const {
	return m_texturesList;
}

bool Textures::removeAccents() const {
	return !m_accents;
}

QColor Textures::primaryColor() const {
	return m_primaryColor;
}

QColor Textures::secondaryColor() const {
	return m_secondaryColor;
}

QColor Textures::tertiaryColor() const {
	return m_tertiaryColor;
}

QPixmap Textures::loadPixmap(QString path) const {
	//On charge l'image du pack de texture
	QPixmap pixmap(m_texturesFolder.path() + "/" + m_texturesAvailable[m_currentTexturesPack] + "/" + path);

	//Si l'image est nulle, on utilise celle du fichier .qrc
	if(pixmap.isNull())
		return QPixmap(":resources/" + path);

	return pixmap;
}

QPixmap Textures::loadRotatedPixmap(QString imagePath, int angle) const {
	return loadPixmap(imagePath).transformed(QMatrix().rotate(angle)); // On appel loadPixmap() et on tourne l'image
}

QFont Textures::loadFont(int pointSize) const {
	return QFont(m_fontName, pointSize); //On charge la police
}

QUrl Textures::loadSoundUrl(QString soundPath) const {
	//Si le fichier de son n'existe pas, on return une QURL vide
	if(!QFile(m_texturesFolder.path() + "/" + m_texturesAvailable[m_currentTexturesPack] + "/sounds/" + soundPath).exists())
		return QUrl("");

	//Sinon on renvoit l'url demandée
	return QUrl(m_texturesFolder.path() + "/" + m_texturesAvailable[m_currentTexturesPack] + "/sounds/" + soundPath);
}
