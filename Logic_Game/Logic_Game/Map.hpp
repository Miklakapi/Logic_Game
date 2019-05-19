#pragma once

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <string>

#include "Square.hpp"
#include "MapReader.hpp"

using namespace sf;
using namespace std;

class Map{

	Square* square;

	MapReader reader;

public:

	Map();

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