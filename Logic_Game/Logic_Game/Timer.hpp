#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Timer : public Clock{

	Font font;

	Text text;

	Clock clock;

	int minutes;

	int seconds;

public:

	Timer(Vector2f position = Vector2f{ 0,0 }, string fontFile = "Fonts/IndieFlower.ttf" );

	void setTimerFont(string fontFile);

	void setPosition(Vector2f position);

	int getMinutes();

	int getSeconds();

	void refresh();

	void draw(RenderWindow& window);

	void resetTime();
};