#ifndef GRAPHICSLABELITEM_H
#define GRAPHICSLABELITEM_H

#include <QGraphicsTextItem>
#include <QTextDocument>
#include <QTextOption>
#include "src/Core/gamecore.h"

class GraphicsLabelItem : public QGraphicsTextItem {
public:
	GraphicsLabelItem(GameCore* game, QString text, int fontSize, QGraphicsItem* parent = nullptr);

	void update();
	void setText(QString str);

private:
	Textures* m_textures;
	Translator* m_tr;

	QString m_text;
	int m_fontSize;

};

#endif // GRAPHICSLABELITEM_H
