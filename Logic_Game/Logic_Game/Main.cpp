#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Spikes.hpp"
#include "Map.hpp"
#include "MenuBar.hpp"
#include "SlidingBlock.hpp"
#include "VectorConverter.hpp"
#include "Plate.hpp"
#include "TeleportField.hpp"
#include "Door.hpp"

using namespace sf;

int main() {
	RenderWindow app(VideoMode{ 1440,880 }, "Logic_Game", Style::Close);
	app.setFramerateLimit(60);


	Map map;
	map.renderLV(1);
	MenuBar menuBar;
	Spikes spikes[12];
	Spikes* spike = spikes;
	(spike + 0)->setPosition(VectorConverter::convert(6, 1).asVector2f());
	(spike + 1)->setPosition(VectorConverter::convert(6, 2).asVector2f());
	(spike + 2)->setPosition(VectorConverter::convert(6, 3).asVector2f());
	(spike + 3)->setPosition(VectorConverter::convert(8, 1).asVector2f());
	(spike + 4)->setPosition(VectorConverter::convert(8, 2).asVector2f());
	(spike + 5)->setPosition(VectorConverter::convert(8, 3).asVector2f());
	(spike + 6)->setPosition(VectorConverter::convert(9, 1).asVector2f());
	(spike + 7)->setPosition(VectorConverter::convert(9, 2).asVector2f());
	(spike + 8)->setPosition(VectorConverter::convert(9, 3).asVector2f());
	(spike + 9)->setPosition(VectorConverter::convert(11, 1).asVector2f());
	(spike + 10)->setPosition(VectorConverter::convert(11, 2).asVector2f());
	(spike + 11)->setPosition(VectorConverter::convert(11, 3).asVector2f());

	SlidingBlock block;
	block.setPosition(VectorConverter::convert(2,2).asVector2f());

	Plate plate(VectorConverter::convert(1, 1).asVector2f());

	Door door(VectorConverter::convert(3, 3).asVector2f());

	TeleportField teleport(VectorConverter::convert(4, 4).asVector2f());
	teleport.setOpen(true);

	while (app.isOpen()) {

		Event event;
		while (app.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				app.close();
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			block.push(SlidingBlock::Direction::Up);
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			block.push(SlidingBlock::Direction::Left);
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			block.push(SlidingBlock::Direction::Down);
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			block.push(SlidingBlock::Direction::Right);
		}

		if (block.getExist()) {
			for (int i = 0; i < 12; i++) {
				if (!(spike + i)->getDmg()) continue;
				if (block.getPosition().x + 80 > (spike + i)->getPosition().x &&
					block.getPosition().x < (spike + i)->getPosition().x + 80 &&
					block.getPosition().y + 80 >(spike + i)->getPosition().y &&
					block.getPosition().y < (spike + i)->getPosition().y + 80) {
					block.destroy();
				}
			}
			if (block.getPosition().x + 80 > plate.getPosition().x &&
				block.getPosition().x < plate.getPosition().x + 80 &&
				block.getPosition().y + 80 >plate.getPosition().y &&
				block.getPosition().y < plate.getPosition().y + 80) {
				plate.setPressure(true);
			}
			else {
				plate.setPressure(false);
			}
			door.setOpen(plate.isPressed());

			if (block.getPosition().x == teleport.getPosition().x &&
				block.getPosition().y == teleport.getPosition().y) {
				block.setPosition(VectorConverter::convert(15, 5).asVector2f());
			}
		}

		block.run();
		menuBar.run();

		app.clear(Color::White);
		map.draw(app);
		menuBar.draw(app);
		for (int i = 0; i < 12; i++) {
			(spike + i)->draw(app);
		}
		plate.draw(app);
		door.draw(app);
		teleport.draw(app);
		block.draw(app);
		app.display();
	}
}