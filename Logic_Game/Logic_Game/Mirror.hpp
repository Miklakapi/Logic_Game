#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;

class Mirror : public RectangleShape{

	bool exist;

public:

	Mirror();
	
	void destroy();

	bool getExist();

};