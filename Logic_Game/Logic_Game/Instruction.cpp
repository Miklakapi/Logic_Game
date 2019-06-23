#include "Instruction.hpp"

Instruction::Instruction(string textureFile) {
	texture.loadFromFile(textureFile);
	setSize(Vector2f{ 1440,880 });
	setPosition(Vector2f{ 0,0 });
	setTexture(&texture);
	clickDelay.restart();
}

Instruction::Type Instruction::run(RenderWindow& window) {

	if (Mouse::isButtonPressed(Mouse::Left) && clickDelay.getElapsedTime().asSeconds() >= 0.2) {
		clickDelay.restart();

		Vector2f pos = { float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y) };

		if (pos.x >= 495 && pos.x <= 945) {

			if (pos.y >= 737 && pos.y <= 850) {

				return Type::Return;
			}
		}
	}

	return None;
}

void Instruction::draw(RenderWindow& window) {
	window.draw(*this);
}