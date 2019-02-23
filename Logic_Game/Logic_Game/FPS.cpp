#include "FPS.hpp"

FPS::FPS(Vector2f position, string fontFile){
	setCharacterSize(20);
	setFPSFont(fontFile);
	setFillColor(Color::Green);
	setLetterSpacing(1);
	setStyle(Text::Bold);
	setPosition(position);
}

void FPS::setFPSFont(string fontFile) {
	font.loadFromFile(fontFile);
	setFont(font);
}

void FPS::setOn(bool on) {
	this->on = on;
}

bool FPS::isOn() {
	return on;
}

void FPS::run() {
	if (!on) return;
	if (delay.getElapsedTime().asSeconds() >= 1) {
		delay.restart();
		setString("FPS: " + to_string(int(1 / clock.restart().asSeconds())));
	}
	else {
		clock.restart();
	}
}