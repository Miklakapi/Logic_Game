#include "Menu.hpp"

Menu::Menu(){
	setSize({ 1440,880 });
	rec1.setSize({ 400,400 });
	rec2.setSize({ 400,400 });
	rec3.setSize({ 400,400 });
	rec4.setSize({ 400,400 });

	rec1.setOrigin({ 200,200 });
	rec2.setOrigin({ 200,200 });
	rec3.setOrigin({ 200,200 });
	rec4.setOrigin({ 200,200 });

	rec2.setPosition({ 1440,0 });
	rec3.setPosition({ 0,880 });
	rec4.setPosition({ 1440,880 });

	texture = new Texture[2];
	(texture + 0)->loadFromFile("Img/Menu.png");
	(texture + 1)->loadFromFile("Img/Gear.png");

	setTexture(texture);
	rec1.setTexture((texture + 1));
	rec2.setTexture((texture + 1));
	rec3.setTexture((texture + 1));
	rec4.setTexture((texture + 1));
}

Menu::Type Menu::run(RenderWindow& window, bool on) {
	if (clock.getElapsedTime().asSeconds() >= 0.05) {
		clock.restart();
		rec1.rotate(3);
		rec2.rotate(-3);
		rec3.rotate(-3);
		rec4.rotate(3);
	}
	if (Mouse::isButtonPressed(Mouse::Left) && on) {
		Vector2f pos = { float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y) };

		if (pos.x >= 495 && pos.x <= 945 &&
			pos.y >= 165 && pos.y <= 850) {

			if (pos.y <= 278) return Type::Play;
			else if (pos.y >= 308 && pos.y <= 421) return Type::Editor;
			else if (pos.y >= 451 && pos.y <= 564) return Type::Instruction;
			else if (pos.y >= 594 && pos.y <= 707) return Type::Options;
			else if (pos.y >= 737 && pos.y <= 850) return Type::Exit;
		}
	}
	return Type::None;
}

void Menu::draw(RenderWindow& window, bool on) {
	if(on) window.draw(*this);
	window.draw(rec1);
	window.draw(rec2);
	window.draw(rec3);
	window.draw(rec4);
}

Menu::~Menu() {
	delete [] texture;
}