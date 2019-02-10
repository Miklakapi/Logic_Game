#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class LvInfo : public Text{

	Font font;

	int lv;

public:

	LvInfo(Vector2f position = Vector2f{ 0,0 }, string fontFile = "Fonts/IndieFlower.ttf");

	void setLV(int lv);

	int getLV();

	void reset();
};