#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "VectorConverter.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "SlidingBlock.hpp"
#include "Mirror.hpp"
#include "Door.hpp"
#include "ShootingBlock.hpp"
#include "LaserMachine.hpp"

using namespace sf;

class HelpClass{

public:
	
	void move(Player& player, Map& map, SlidingBlock* block, int number, Mirror* mirror, int number2, Door* door, int number3,
		ShootingBlock* blockS, int number4, LaserMachine* machine, int number5);
	

};