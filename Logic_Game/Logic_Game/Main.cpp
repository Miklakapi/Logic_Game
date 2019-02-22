#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Map.hpp"
#include "Plate.hpp"
#include "VectorConverter.hpp"
#include "Door.hpp"
#include "Spikes.hpp"

using namespace sf;

int main() {
	RenderWindow app(VideoMode{ 1440,880 }, "Logic_Game", Style::Close);
	app.setFramerateLimit(60);
	//-------
	Map map;
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
	spikes.setOn(false);
	//-------

	while (app.isOpen()) {

		Event event;
		while (app.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				app.close();
				break;
			case Event::KeyPressed:
				spikes.setOn(true);
				break;
			}
		}

		//-------
		spikes.run();
		//-------

		app.clear();
		map.draw(app);
		(plate + 0)->draw(app);
		(plate + 1)->draw(app);
		door.draw(app);
		spikes.draw(app);
		app.display();
	}
}