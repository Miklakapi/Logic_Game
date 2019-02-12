#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Spikes.hpp"
#include "Map.hpp"
#include "MenuBar.hpp"
#include "SlidingBlock.hpp"
#include "VectorConverter.hpp"

using namespace sf;

int main() {
	RenderWindow app(VideoMode{ 1440,880 }, "Logic_Game", Style::Close);
	app.setFramerateLimit(60);


	Map map;
	map.renderLV(1);
	MenuBar menuBar;
	Spikes spikes[12];
	Spikes* spike = spikes;
	(spike + 0)->setPosition(VectorConverter::convert(6,1).asVector2f());
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
	block.setPosition(VectorConverter::convert(19).asVector2f());

	while (app.isOpen()) {

		Event event;
		while (app.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				app.close();
				break;
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