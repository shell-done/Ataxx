#ifndef TEXTURES_H
#define TEXTURES_H

#include <QObject>
#include <QMap>
#include <QDir>
#include <QColor>
#include <QStringList>
#include <QTextStream>
#include <QPixmap>
#include <QFont>
#include <iostream>

typedef struct s_textures_pack {
	QString name;
	QString description;
} s_textures_pack;

class Textures : public QObject {
	Q_OBJECT

public:
	Textures(QString texturesPackFolder, QObject *parent = nullptr);

	QList<s_textures_pack> getPackList() const;
	bool useAccents() const;
	QColor primaryColor() const;

	QPixmap loadPixmap(QString imagePath) const;
	QFont loadFont(int pointSize) const;

private:
	static const QString defaultTexturesPack;

	bool loadPack();

	QDir m_texturesFolder;
	QMap<QString, QString> m_texturesAvailable;
	QList<s_textures_pack> m_texturesList;

	QString m_currentTexturesPacks;
	QString m_description;
	bool m_accents;
	QColor m_primaryColor;
	QString m_fontName;

signals:
	void updateTextures();
};

#endif // TEXTURES_H
