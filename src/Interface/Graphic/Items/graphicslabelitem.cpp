#include "graphicslabelitem.h"

GraphicsLabelItem::GraphicsLabelItem(GameCore* game, QString text, int fontSize, QGraphicsItem* parent) : QGraphicsTextItem(parent) {
	m_textures = game->textures();
	m_tr = game->tr();
	m_text = text;
	m_fontSize = fontSize;

	QTextOption option = document()->defaultTextOption();
	option.setAlignment(Qt::AlignCenter);
	document()->setDefaultTextOption(option);
}

void GraphicsLabelItem::update() {
	setPlainText(m_tr->qTranslate(m_text, m_textures->removeAccents()));
	setDefaultTextColor(m_textures->primaryColor());
	setFont(m_textures->loadFont(m_fontSize));
}

void GraphicsLabelItem::setText(QString str) {
	m_text = str;
	setPlainText(m_tr->qTranslate(str, m_textures->removeAccents()));
}
