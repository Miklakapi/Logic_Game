#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "Square.hpp"
#include "MapReader.hpp"

using namespace std;
using namespace sf;

class Map{

	Square* square;

	MapReader reader;

public:

	Map();

	static void setSquareTexture(string textureFile = "Img/Square.png");

	void setType(int number, Square::Type type);

	Square::Type getType(int number);

	void loadLV(int lv);

	void renderLV();

	void renderLV(int lv);

	int getActualLV();

	void draw(RenderWindow& window);

	void reset();

	~Map();
};

