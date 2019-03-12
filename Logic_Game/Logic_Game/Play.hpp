#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "VectorConverter.hpp"
#include "Map.hpp"
#include "MenuBar.hpp"
#include "SlidingBLocks.hpp"
#include "Mirrors.hpp"
#include "LaserMachines.hpp"
#include "ShootingBlocks.hpp"
#include "Plates.hpp"
#include "Doors.hpp"
#include "TeleportFields.hpp"
#include "Traps.hpp"
#include "Player.hpp"
#include "HelpClass.hpp"




using namespace sf;
using namespace std;

class Play{




public:
	
	Play();
	
	void run();

	void draw(RenderWindow& window);

	~Play();
};