#ifndef TEXTURES_H
#define TEXTURES_H

/*!
 * \file textures.h
 * \brief Fichier de la classe Textures
 *
 * \author Alexandre THOMAS
 * \version 1.0
 */

#include <QObject>
#include <QFontDatabase>
#include <QMap>
#include <QDir>
#include <QColor>
#include <QStringList>
#include <QTextStream>
#include <QPixmap>
#include <QFont>
#include <QMatrix>
#include <QUrl>
#include <iostream>

/**
 * \struct s_textures_pack
 * \brief Objet représentant un pack de textures
 *
 * Chaque structure contient le nom, la description et l'icon du pack de texture
 */
typedef struct s_textures_pack {
	QString name;
	QString description;
	QImage icon;
} s_textures_pack;

/*!
 * \class Textures textures.h
 * \brief Classe représentant le pack de texture utilisé
 *
 * La classe fournit la liste des packs de textures trouvés ainsi que des méthodes permettant d'accéder aux ressources du pack utilisé
 * Si aucun texture pack n'est trouvé, les images de bases du fichier qrc sont utilisées
 *
 * Pour plus d'informations sur la structure d'un pack de texture, se reporter au fichier readme.md
 */
class Textures : public QObject {
	Q_OBJECT

public:
	/*!
	 * \brief Constructeur
	 *
	 * \param texturesPackFolder Le dossier contenant les packs de textures
	 * \param parent Parent de l'objet
	*/
	Textures(QString texturesPackFolder, QObject *parent = nullptr);

	/*!
	 * \brief Renvoie le pack de textures actuel
	 *
	 * \return Le nom du pack de textures actuel, la chaine vide si aucun pack n'a été chargé
	*/
	QString currentTexturePack() const;

	/*!
	 * \brief Renvoie l'index du pack de textures actuel
	 *
	 * \return Renvoie l'index du pack de textures actuel dans la liste des packs, ou -1 si aucun pack n'a été chargé
	*/
	int currentTexturePackIdx() const;

	/*!
	 * \brief Définit le texture pack courant
	 *
	 * \param name Le nom du pack de textures à utiliser
	*/
	void setTexturePack(QString& name);

	/*!
	 * \brief Définit le texture pack courant
	 *
	 * \param idx L'index du pack de textures à utiliser
	*/
	void setTexturePackIdx(int idx);

	/*!
	 * \brief Renvoie la liste des packs de textures trouvés
	 *
	 * \return Une liste de structure s_textures_pack contenant les informations de tous les packs de textures trouvéss
	*/
	QList<s_textures_pack> getPackList() const;

	/*!
	 * \brief Précise si les accents doivent être supprimés ou non des chaines de caractères (pour certaines polices)
	 *
	 * \return true si les accents doivent être supprimés, false sinon
	*/
	bool removeAccents() const;

	/*!
	 * \brief Renvoie la couleur primaire définie dans le pack de texture
	 *
	 * \return La couleur primaire définie dans le pack de texture
	*/
	QColor primaryColor() const;

	/*!
	 * \brief Renvoie la couleur secondaire définie dans le pack de texture
	 *
	 * \return La couleur secondaire définie dans le pack de texture
	*/
	QColor secondaryColor() const;

	/*!
	 * \brief Renvoie la couleur tertiaire définie dans le pack de texture
	 *
	 * \return La couleur tertiaire définie dans le pack de texture
	*/
	QColor tertiaryColor() const;

	/*!
	 * \brief Charge l'image en question depuis le dossier du pack de texture.
	 *
	 * Si l'image n'est pas trouvée, c'est l'image par défaut qui est utilisée
	 *
	 * \param imagePath Le chemin de l'image (relativement au dossier du pack de texture)
	 * \return L'image demandée dans le pack de textures
	*/
	QPixmap loadPixmap(QString imagePath) const;

	/*!
	 * \brief Charge l'image en question depuis le dossier du pack de texture puis la tourne.
	 *
	 * Si l'image n'est pas trouvée, c'est l'image par défaut qui est utilisée
	 *
	 * \param imagePath Le chemin de l'image (relativement au dossier du pack de texture)
	 * \param angle L'angle de rotation de l'image en degrés
	 * \return L'image demandée dans le pack de textures
	*/
	QPixmap loadRotatedPixmap(QString imagePath, int angle) const;

	/*!
	 * \brief Charge la police de du pack avec la taille spécifiée en paramètre
	 *
	 * \param pointSize La taille de police en point
	 *
	 * \return La police du pack de texture
	*/
	QFont loadFont(int pointSize) const;

	/*!
	 * \brief Renvoie l'url du fichier de son du pack de texture
	 *
	 * \param soundPath Le chemin du fichier de son (relativement au dossier du pack de texture)
	 * \return L'url du fichier de son
	*/
	QUrl loadSoundUrl(QString soundPath) const;

private:
	static const QString defaultTexturesPack; /*!< Le nom du pack de texture par défaut */

	/*!
	 * \brief Charge les informations du pack de texture m_currentTexturePack
	 *
	 * Si defaultPack vaut true, alors ce sont les informations du pack de textures stocké dans le .qrc qui est utilisé
	 *
	 * \return true si le chargement s'est passé correctement, false sinon
	*/
	bool loadPack(bool defaultPack = false);

	/*!
	 * \brief Renvoie une QColor associé à un QString de la forme "r,g,b"
	 *
	 * \param La chaine de caractère à traiter
	 * \return Un QColor associé, si la chaine de caractère est invalide, renvoie blanc.
	*/
	QColor loadColor(const QString& str);

	QDir m_texturesFolder; /*!< Le dossier du pack de texture courant */
	QMap<QString, QString> m_texturesAvailable; /*!< Une map entre le nom d'affichage et le nom du dossier des packs de textures */
	QList<s_textures_pack> m_texturesList; /*!< La liste des packs de textures */

	bool m_useDefault; /*!< Pour savoir si les ressources par défaut (celles du .qrc) sont utilisées */

	QString m_currentTexturesPack; /*!< Le nom du pack de texture actuel */
	QString m_description; /*!< Description du pack de texture actuel */
	bool m_accents; /*!< Pour savoir si le pack de texture actuel demande d'enlever les accents */
	QColor m_primaryColor; /*!< Couleur primaire du pack */
	QColor m_secondaryColor; /*!< Couleur secondaire du pack */
	QColor m_tertiaryColor; /*!< Couleur tertiaire du pack */
	QString m_fontName; /*!< Nom de la police à utiliser */

signals:
	void updateTextures(); /*!< Signal que les textures doivent être mises à jour */
};

#endif // TEXTURES_H
