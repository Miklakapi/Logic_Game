#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>
#include "Square.hpp"

using namespace std;
using namespace sf;

class MapReader{

	Square::Type* type;

	int actualLv;

public:

	MapReader();

	void loadLV(int lv);

	void renderLV(Square* square);

	void renderLV(int lv, Square* square);

	int getActualLV();

	~MapReader();
};

