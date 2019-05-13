#include "textures.h"

#include <QDebug>

using namespace std;

const QString Textures::defaultTexturesPack = "Original";

Textures::Textures(QString textFolder, QObject *parent) : QObject(parent), m_texturesFolder(textFolder) {
	m_currentTexturesPacks = "";
	QStringList texturesList = m_texturesFolder.entryList(QDir::Dirs);

	for(const QString& texturesPackFolder : texturesList) {
		QFile textPackConfigFile(m_texturesFolder.path() + "/" + texturesPackFolder + "/pack.conf");

		if(textPackConfigFile.open(QIODevice::ReadOnly)) {
			QTextStream in(&textPackConfigFile);
			QString line = in.readLine();

			QStringList data = line.split(" = ");
			if(data[0] != "pack_name") {
				textPackConfigFile.close();
				continue;
			}
			QString packName = data[1];
			if(m_texturesAvailable.keys().contains(packName)) {
				textPackConfigFile.close();
				continue;
			}
			if(m_texturesAvailable.keys().contains(packName)) {
				textPackConfigFile.close();
				continue;
			}
			m_texturesAvailable.insert(packName, texturesPackFolder);

			if(packName == defaultTexturesPack)
				m_currentTexturesPacks = packName;

			line = in.readLine();
			data = line.split(" = ");

			QString description;
			if(data[0] == "description")
				description = data[1];
			else
				description = "";

			s_textures_pack pack = {packName, description};
			m_texturesList << pack;

			textPackConfigFile.close();
		}
	}

	if(m_texturesAvailable.isEmpty()) {
		m_currentTexturesPacks = "";
		cerr << "[WARNING] No textures packs found" << endl;
		return;
	}

	if(m_currentTexturesPacks == "") {
		m_currentTexturesPacks = m_texturesAvailable.firstKey();
	}


	if(!loadPack()) {
		m_currentTexturesPacks = "";
		QString error = "[WARNING] Can't read textures pack config file : " + m_currentTexturesPacks;
		cerr << error.toStdString() << endl;
	}
}

bool Textures::loadPack() {
	QFile textPackConfigFile(m_texturesFolder.path() + "/" + m_currentTexturesPacks + "/pack.conf");

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

QList<s_textures_pack> Textures::getPackList() const {
	return m_texturesList;
}

bool Textures::useAccents() const {
	return m_accents;
}

QColor Textures::primaryColor() const {
	return m_primaryColor;
}

QColor Textures::secondaryColor() const {
	return m_secondaryColor;
}

QPixmap Textures::loadPixmap(QString path) const {
	QPixmap pixmap(m_texturesFolder.path() + "/" + m_currentTexturesPacks + "/" + path);

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
