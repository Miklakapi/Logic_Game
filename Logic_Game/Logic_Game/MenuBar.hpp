#pragma once

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <string>

#include "Hearts.hpp"
#include "LvInfo.hpp"
#include "Timer.hpp"
#include "Data.hpp"

using namespace sf;
using namespace std;

class MenuBar{

	Hearts hearts;
	
	LvInfo lvInfo;

	Timer timer;

public:

	MenuBar();

	void setHeartsTexture(string textureFile);

	void setInfoFont(string fontFile);

	void setTimerFont(string fontFile);

	void setHeartsPosition(Vector2f position);

	void setInfoPosition(Vector2f position);

	void setTimerPosition(Vector2f position);

	Data getData();

	void setHealth(int health);

	void setLV(int lv);

	void run();

	void draw(RenderWindow& window);

	void reset();
};