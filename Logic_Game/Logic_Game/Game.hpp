#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Intro.hpp"
#include "Menu.hpp"

using namespace sf;

class Game{

	enum Type {
		InIntro,
		InMenu,
		InGame,
		InEditor,
		InInstruction,
		InOptions,
	};

	Intro* intro;

	Menu* menu;




	Type type;

public:

	Game();

	void run(RenderWindow& window);

	void draw(RenderWindow& window);

	~Game();
};