#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Spikes.hpp"
#include "Map.hpp"
#include "MenuBar.hpp"
#include "SlidingBlock.hpp"

using namespace sf;

int main() {
	RenderWindow app(VideoMode{ 1440,880 }, "Logic_Game", Style::Close);
	app.setFramerateLimit(60);


	Map map;
	map.renderLV(1);
	MenuBar menuBar;
	Spikes spikes[12];
	Spikes* spike = spikes;
	(spike + 0)->setPosition(Vector2f{ 480,160 });
	(spike + 1)->setPosition(Vector2f{ 480,80 });
	(spike + 2)->setPosition(Vector2f{ 480,240 });
	(spike + 3)->setPosition(Vector2f{ 640,80 });
	(spike + 4)->setPosition(Vector2f{ 640,160 });
	(spike + 5)->setPosition(Vector2f{ 640,240 });
	(spike + 6)->setPosition(Vector2f{ 720,80 });
	(spike + 7)->setPosition(Vector2f{ 720,160 });
	(spike + 8)->setPosition(Vector2f{ 720,240 });
	(spike + 9)->setPosition(Vector2f{ 880,80 });
	(spike + 10)->setPosition(Vector2f{ 880,160 });
	(spike + 11)->setPosition(Vector2f{ 880,240 });

	SlidingBlock block;

	while (app.isOpen()) {

		Event event;
		while (app.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				app.close();
				break;
			case Event::KeyPressed:
				switch (event.key.code) {
				case Keyboard::W:
					block.push(Direction::Up);
					break;
				case Keyboard::A:
					block.push(Direction::Left);
					break;
				case Keyboard::S:
					block.push(Direction::Down);
					break;
				case Keyboard::D:
					block.push(Direction::Right);
					break;
				}
			}
		}
		app.clear(Color::White);
		map.draw(app);
		menuBar.draw(app);
		for (int i = 0; i < 12; i++) {
			(spike + i)->draw(app);
		}
		block.draw(app);
		app.display();
	}
}