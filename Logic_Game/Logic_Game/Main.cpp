#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "ShootingBlock.hpp"
#include "Game.hpp"

using namespace sf;
using namespace std;

int main() {
	RenderWindow app(VideoMode{ 1440,880 }, "Logic_Game", Style::Close);
	app.setFramerateLimit(144);

	Game game(app);


	while (app.isOpen()) {

		//fps.run();

		Event event;
		while (app.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				app.close();
				break;
			}
		}


		game.run(app);

		//
		app.clear();

		game.draw(app);

		app.display();
	}
}