#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;

class Menu : public RectangleShape{

public:

	enum Type {
		None,
		Play,
		Editor,
		Instruction,
		Options,
		Exit
	};

private:

	Texture* texture;

	RectangleShape rec1;

	RectangleShape rec2;

	RectangleShape rec3;

	RectangleShape rec4;

	Clock clock;

public:
	
	Menu();
	
	Type run(RenderWindow& window);

	void draw(RenderWindow& window);

	~Menu();
};