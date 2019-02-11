#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Spikes.hpp"
#include "Map.hpp"
#include "MenuBar.hpp"

using namespace sf;

int main() {
	RenderWindow app(VideoMode{ 1440,880 }, "Logic_Game", Style::Close);
	app.setFramerateLimit(60);


	Map map;
	map.renderLV(1);
	MenuBar menuBar;
	Spikes spikes(Vector2f{80,80});
	Spikes spik(Vector2f{ 160,80 });

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
		spikes.draw(app);
		spik.draw(app);
		app.display();
	}
}