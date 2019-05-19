#pragma once

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <string>
#include <fstream>

#include "Intro.hpp"
#include "Menu.hpp"
#include "LevelSelect.hpp"
#include "Options.hpp"
#include "FPS.hpp"

using namespace sf;
using namespace std;

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

	//

	LevelSelect* levelSelect;

	Options* options;

	FPS* FpsCounter;

	//

	Type type;

	bool sound;
	bool fpsCounter;

	Clock delayClick;

public:

	Game(RenderWindow& window);

	void run(RenderWindow& window);

	void draw(RenderWindow& window);

	~Game();
};