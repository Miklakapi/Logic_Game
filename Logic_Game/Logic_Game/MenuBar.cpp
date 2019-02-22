#include "MenuBar.hpp"

MenuBar::MenuBar() : hearts(Vector2f{ 20,15 }), lvInfo(Vector2f{ 600,0 }), timer(Vector2f{ 1280,0 }) {
	reset();
}

void MenuBar::setHeartsTexture(string textureFile) {
	hearts.setHeartsTexture(textureFile);
}

void MenuBar::setInfoFont(string fontFile) {
	lvInfo.setInfoFont(fontFile);
}

void MenuBar::setTimerFont(string fontFile) {
	timer.setTimerFont(fontFile);
}

void MenuBar::setHeartsPosition(Vector2f position) {
	hearts.setPosition(position);
}

void MenuBar::setInfoPosition(Vector2f position) {
	lvInfo.setPosition(position);
}

void MenuBar::setTimerPosition(Vector2f position) {
	timer.setPosition(position);
}

Data MenuBar::getData() {
	Data data;
	data.health = hearts.getHealth();
	data.lv = lvInfo.getLV();
	data.minutes = timer.getMinutes();
	data.seconds = timer.getSeconds();
	return data;
}

void MenuBar::setHealth(int health) {
	hearts.setHealth(health);
}

void MenuBar::setLV(int lv) {
	lvInfo.setLV(lv);
}

void MenuBar::run() {
	timer.refresh();
}

void MenuBar::draw(RenderWindow& window) {
	hearts.draw(window);
	window.draw(lvInfo);
	timer.draw(window);
}

void MenuBar::reset() {
	hearts.reset();
	lvInfo.reset();
	timer.resetTime();
}