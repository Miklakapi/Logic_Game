#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class Play{



public:
	
	Play();
	
	void run();

	void draw(RenderWindow& window);

	~Play();
};