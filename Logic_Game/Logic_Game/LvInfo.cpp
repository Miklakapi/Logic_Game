#include "LvInfo.hpp"

LvInfo::LvInfo(Vector2f position, string fontFile){
	setCharacterSize(60);
	font.loadFromFile(fontFile);
	setFont(font);
	setFillColor(Color::White);
	setLetterSpacing(1);
	setStyle(Text::Bold);
	setPosition(position);
	reset();
}

void LvInfo::setLV(int lv) {
	this->lv = lv;
	setString("Poziom: " + to_string(lv));
}

int LvInfo::getLV() {
	return lv;
}

void LvInfo::reset() {
	setLV(1);
}