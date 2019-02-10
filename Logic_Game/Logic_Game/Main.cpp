#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Map.hpp"
#include "Hearts.hpp"

using namespace sf;

int main() {
	RenderWindow app(VideoMode{ 1440,880 }, "Logic_Game", Style::Close);
	app.setFramerateLimit(60);

	Map map;
	map.renderLV(1);
	Hearts::setTexture("Img/Empty.png");
	Hearts he;

	while (app.isOpen()) {

		Event event;
		while (app.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				app.close();
				break;
			}
		}
		app.clear(Color{64,64,64});
		map.draw(app);
		he.draw(app);
		app.display();
	}
}