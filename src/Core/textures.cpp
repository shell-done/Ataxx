#include "textures.h"

#include <QDebug>

using namespace std;

const QString Textures::defaultTexturesPack = "The Original";

Textures::Textures(QString textFolder, QObject *parent) : QObject(parent), m_texturesFolder(textFolder) {
	m_currentTexturesPack = "";
	QStringList texturesList = m_texturesFolder.entryList(QDir::Dirs);

	for(const QString& texturesPackFolder : texturesList) {
		QFile textPackConfigFile(m_texturesFolder.path() + "/" + texturesPackFolder + "/pack.conf");

		if(textPackConfigFile.open(QIODevice::ReadOnly)) {
			QTextStream in(&textPackConfigFile);
			QString line = in.readLine();

			QStringList data = line.split(" = ");
			if(data[0] != "pack_name" || data.size() != 2) {
				textPackConfigFile.close();
				continue;
			}

			QString packName = data[1];
			if(m_texturesAvailable.keys().contains(packName)) {
				textPackConfigFile.close();
				continue;
			}

			m_texturesAvailable.insert(packName, texturesPackFolder);

			if(packName == defaultTexturesPack)
				m_currentTexturesPack = packName;

			line = in.readLine();
			data = line.split(" = ");

			QString description;
			if(data[0] == "description" && data.size() == 2)
				description = data[1];
			else
				description = "";

			QImage icon(m_texturesFolder.path() + "/" + texturesPackFolder + "/icon.png");
			s_textures_pack pack = {packName, description, icon};
			m_texturesList << pack;

			textPackConfigFile.close();
		}
	}

	if(m_texturesAvailable.isEmpty()) {
		m_currentTexturesPack = "";
		cerr << "[WARNING] No textures packs found" << endl;
		return;
	}

	if(m_currentTexturesPack == "") {
		m_currentTexturesPack = m_texturesAvailable.firstKey();
	}


	if(!loadPack()) {
		m_currentTexturesPack = "";
		QString error = "[WARNING] Can't read textures pack config file : " + m_currentTexturesPack;
		cerr << error.toStdString() << endl;
	}
}

bool Textures::loadPack() {
	QFile textPackConfigFile(m_texturesFolder.path() + "/" + m_texturesAvailable[m_currentTexturesPack] + "/pack.conf");

	if(textPackConfigFile.open(QIODevice::ReadOnly)) {
		m_description = "No description available";
		m_accents = false;
		m_primaryColor = QColor(255, 255, 255);
		m_fontName = "";

		QTextStream in(&textPackConfigFile);
		in.readLine();
		while(!in.atEnd()) {
			QString line = in.readLine();

			QStringList data = line.split(" = ");

			if(data.size() != 2)
				continue;

			if(data[0] == "description")
				m_description = data[1];

			if(data[0] == "font") {
				data.takeFirst();

				QString font = data.join(" ");
				m_fontName = font;
			}

			if(data[0] == "use_accents") {
				if(data[1] == "true")
					m_accents = true;
				else
					m_accents = false;
			}

			if(data[0] == "primary_color")
				m_primaryColor = loadColor(data[1]);

			if(data[0] == "secondary_color")
				m_secondaryColor = loadColor(data[1]);

			if(data[0] == "tertiary_color")
				m_tertiaryColor = loadColor(data[1]);
		}

		textPackConfigFile.close();
		return true;
	}

	return false;
}

QColor Textures::loadColor(const QString &str) {
	QColor color;

	QStringList rgb = str.split(",");
	bool ok;
	bool rgbOk = true;
	int components[3];

	for(int i=0; i<3; i++) {
		components[i] = rgb[i].toInt(&ok);
		if(!ok || components[i] < 0 || components[i] > 255)
			rgbOk = false;
	}

	if(rgbOk)
		color = QColor(components[0], components[1], components[2]);
	else
		color = QColor(255, 255, 255);

	return color;
}

QString Textures::currentTexturePack() const {
	return m_currentTexturesPack;
}

int Textures::currentTexturePackIdx() const {
	for(int i=0; i<m_texturesList.size(); i++)
		if(m_texturesList[i].name == m_currentTexturesPack)
			return m_texturesList.size() - i - 1;

	return -1;
}

void Textures::setTexturePack(QString& name) {
	if(!m_texturesAvailable.keys().contains(name)) {
		cerr << "[WARNING] Unknown pack : " << name.toStdString() << endl;
		return;
	}

	QString prevPack = m_currentTexturesPack;
	m_currentTexturesPack = name;


	if(!loadPack()) {
		cerr << "[WARNING] Error while loading pack : " << name.toStdString() << endl;
		m_currentTexturesPack = prevPack;
		loadPack();
	}

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
	QPixmap pixmap(m_texturesFolder.path() + "/" + m_texturesAvailable[m_currentTexturesPack] + "/" + path);

	if(pixmap.isNull())
		cerr << "Null pixmap : " << path.toStdString() << endl;

	return pixmap;
}

QPixmap Textures::loadRotatePixmap(QString imagePath, int angle) const {
	return loadPixmap(imagePath).transformed(QMatrix().rotate(angle));
}

QFont Textures::loadFont(int pointSize) const {
	return QFont(m_fontName, pointSize);
}

QUrl Textures::loadSoundUrl(QString soundPath) const {
	return QUrl(m_texturesFolder.path() + "/" + m_texturesAvailable[m_currentTexturesPack] + "/sounds/" + soundPath);
}
