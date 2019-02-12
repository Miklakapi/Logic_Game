#include "Timer.hpp"

Timer::Timer(Vector2f position, string fontFile) {
	text.setCharacterSize(60);
	font.loadFromFile(fontFile);
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setLetterSpacing(1);
	text.setStyle(Text::Bold);
	setPosition(position);
}

void Timer::setPosition(Vector2f position) {
	text.setPosition(position);
}

int Timer::getMinutes() {
	return minutes;
}

int Timer::getSeconds() {
	return seconds;
}

void Timer::refresh() {
	if (clock.getElapsedTime().asSeconds() >= 0.5) {
		clock.restart();
		string str1, str2;
		seconds = int(int(getElapsedTime().asSeconds()) % 60);
		if (seconds < 10) str2 = "0";
		else str2 = "";
		minutes = int(int(getElapsedTime().asSeconds()) / 60);
		if (minutes < 10)str1 = "0";
		else str1 = "";
		string str;
		if (minutes < 60) str = str1 + to_string(minutes) + ":" + str2 + to_string(seconds);
		else str = "60:00";
		text.setString(str);
	}
}

void Timer::draw(RenderWindow& window) {
	window.draw(text);
}

void Timer::resetTime() {
	restart();
	clock.restart();
}