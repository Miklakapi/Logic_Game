#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;

class Player : public RectangleShape{

public:

	Player();

	void setLive(bool live);

};