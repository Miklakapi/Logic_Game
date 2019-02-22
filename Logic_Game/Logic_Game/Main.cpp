#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Map.hpp"
#include "MenuBar.hpp"
#include "Plate.hpp"
#include "VectorConverter.hpp"
#include "Door.hpp"
#include "Spikes.hpp"
#include "Player.hpp"

using namespace sf;

int main() {
	RenderWindow app(VideoMode{ 1440,880 }, "Logic_Game", Style::Close);
	app.setFramerateLimit(60);
	//-------
	Map::setSquareTexture();

	Map map;
	//-------


	MenuBar menu;
	//-------	
	Plate::setPlateTexture();

	Plate plate[2];
	Plate* pl = plate;
	(pl + 0)->setPlatePosition(VectorConverter::convert(1, 1).asVector2f());
	(pl + 1)->setPlatePosition(VectorConverter::convert(2, 2).asVector2f());
	//-------
	Door::setDoorTexture();

	Door door;
	door.setDoorPosition(VectorConverter::convert(1, 2).asVector2f());
	//-------
	Spikes::loadSpikesTexture();

	Spikes spikes;
	spikes.setPosition(VectorConverter::convert(1, 3).asVector2f());
	spikes.setOn(true);
	//-------
	Player player;
	player.setPosition(VectorConverter::convert(2, 1).asVector2f());
	//-------
	while (app.isOpen()) {

		Event event;
		while (app.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				app.close();
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::W)) player.movePlayer(Player::Up);
		else if (Keyboard::isKeyPressed(Keyboard::A)) player.movePlayer(Player::Left);
		else if (Keyboard::isKeyPressed(Keyboard::S)) player.movePlayer(Player::Down);
		else if (Keyboard::isKeyPressed(Keyboard::D)) player.movePlayer(Player::Right);

		//-------
		spikes.run();
		menu.run();
		player.run();
		//-------
		spikes.run(player);
		(plate + 0)->run(player);
		(plate + 1)->run(player);
		//-------

		app.clear();
		map.draw(app);
		(plate + 0)->draw(app);
		(plate + 1)->draw(app);
		door.draw(app);
		spikes.draw(app);
		menu.draw(app);
		player.draw(app);
		app.display();
	}
}