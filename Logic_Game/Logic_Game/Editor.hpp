#pragma once

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <string>
#include <fstream>

#include "LaserReceiver.hpp"
#include "ShootingBlock.hpp"
#include "LaserMachine.hpp"
#include "Mirror.hpp"
#include "Screen.hpp"

using namespace sf;
using namespace std;

class Editor{

public:

	enum Type {
		None,
		Exit
	};

private:

	Clock delayClock;

	Screen::Stage stage;

	Screen* screen;

public:
	
	Editor();
	
	Type run(RenderWindow& window);

	void draw(RenderWindow& window);

	~Editor();
};