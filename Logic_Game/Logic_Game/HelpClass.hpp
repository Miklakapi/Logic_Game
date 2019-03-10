#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "VectorConverter.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "SlidingBlocks.hpp"
#include "Mirrors.hpp"
#include "Doors.hpp"
#include "ShootingBlocks.hpp"
#include "LaserMachines.hpp"
#include "Traps.hpp"
#include "TeleportFields.hpp"
#include "Plates.hpp"
#include "MenuBar.hpp"

using namespace sf;

class HelpClass{

public:
	
	static void move(Player& player, Map& map, SlidingBlock* block, int number, Mirror* mirror, int number2, Door* door, int number3,
		ShootingBlock* blockS, int number4, LaserMachine* machine, int number5);
	
	static void runAll(MenuBar& menu, Map& map, TeleportFields& fields, Plates& plates, Traps& traps, Player& player, SlidingBlocks& block, Mirrors& mirror, Doors& door, ShootingBlocks& blockS, LaserMachines& machine);

	static void resetAll(MenuBar& menu, Map& map, Player& player, SlidingBlocks& block, Mirrors& mirror, Doors& door, ShootingBlocks& blockS, LaserMachines& machine);

	static void drawAll(RenderWindow& window, MenuBar& menu, Map& map, TeleportFields& fields, Plates& plates, Traps& traps, Player& player, SlidingBlocks& block, Mirrors& mirror, Doors& door, ShootingBlocks& blockS, LaserMachines& machine);
};