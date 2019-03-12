#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Play.hpp"

using namespace sf;
using namespace std;

class LevelSelect : public RectangleShape{

public:

	enum Type {
		None,
		Start,
		Return
	};

private:

	Texture texture;

	Play* play;

	Type type;

public:

	LevelSelect();
	
	Type getType();

	Type run(RenderWindow& window);

	void draw(RenderWindow& window);

	~LevelSelect();
};