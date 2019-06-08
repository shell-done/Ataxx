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
#include <QMatrix>
#include <iostream>

typedef struct s_textures_pack {
	QString name;
	QString description;
	QImage icon;
} s_textures_pack;

class Textures : public QObject {
	Q_OBJECT

public:
	Textures(QString texturesPackFolder, QObject *parent = nullptr);

	QString currentTexturePack() const;
	int currentTexturePackIdx() const;
	void setTexturePack(QString& name);
	void setTexturePackIdx(int idx);

	QList<s_textures_pack> getPackList() const;
	bool useAccents() const;
	QColor primaryColor() const;
	QColor secondaryColor() const;
	QColor tertiaryColor() const;

	QPixmap loadPixmap(QString imagePath) const;
	QPixmap loadRotatePixmap(QString imagePath, int angle) const;
	QFont loadFont(int pointSize) const;

private:
	static const QString defaultTexturesPack;

	bool loadPack();
	QColor loadColor(const QString& str);

	QDir m_texturesFolder;
	QMap<QString, QString> m_texturesAvailable;
	QList<s_textures_pack> m_texturesList;

	QString m_currentTexturesPack;
	QString m_description;
	bool m_accents;
	QColor m_primaryColor;
	QColor m_secondaryColor;
	QColor m_tertiaryColor;
	QString m_fontName;

signals:
	void updateTextures();
};

#endif // TEXTURES_H
