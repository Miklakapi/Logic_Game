#pragma once

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <string>

using namespace sf;
using namespace std;

class Instruction : public RectangleShape{

public: 

	enum Type{
		None,
		Return
	};

private:

	Texture texture;

	Clock clickDelay;

public:
	
	Instruction(string textureFile = "Img/instruction.png");

	Type run(RenderWindow& window);

	void draw(RenderWindow& window);
};