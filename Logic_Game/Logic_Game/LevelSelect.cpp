#include "LevelSelect.hpp"

LevelSelect::LevelSelect(){
	play = new Play;
	type = Type::None;
	setSize({ 1440,880 });
	texture.loadFromFile("Img/LevelSelect.png");
	setTexture(&texture);
}

LevelSelect::Type LevelSelect::getType() {
	return type;
}

LevelSelect::Type LevelSelect::run(RenderWindow& window) {

	if (Mouse::isButtonPressed(Mouse::Left)) {
		Vector2f pos = { float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y) };

		if (pos.x >= 495 && pos.x <= 945) {
			if (pos.y >= 737 && pos.y <= 850) {
				return Type::Return;
			}
		}
	}
	return Type::None;
}

void LevelSelect::draw(RenderWindow& window) {
	window.draw(*this);
}

LevelSelect::~LevelSelect(){
	delete play;
}