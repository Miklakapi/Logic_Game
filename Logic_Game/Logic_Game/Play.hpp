#pragma once

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include "VectorConverter.hpp"
#include "Map.hpp"
#include "MenuBar.hpp"
#include "Player.hpp"
#include "TeleportFields.hpp"
#include "Traps.hpp"
#include "SlidingBLocks.hpp"
#include "Plates.hpp"
#include "Doors.hpp"
#include "ShootingBlocks.hpp"
#include "LaserMachines.hpp"
#include "Mirrors.hpp"
#include "LaserReceivers.hpp"
#include "HelpClass.hpp"

using namespace sf;
using namespace std;

class Play{

	MenuBar* menuBar;

	Map* map;

	//

	Player* player;

	Texture loseTexture;

	Texture winTexture;

	RectangleShape screen;

	bool win;

	Clock winClock;

	VectorConverter winPosition;

	int seconds, minutes;

	Text winTime;

	Font font;

	//

	TeleportFields* teleports;

	Traps* traps;

	SlidingBlocks* blocks;

	Plates* plates;

	Doors* doors;

	ShootingBlocks* blockS;

	LaserMachines* machines;

	Mirrors* mirrors;

	LaserReceivers* receivers;

	VectorConverter startPosition;

public:
	
	Play(int lv, string loseTexture = "Img/loseTexture.png", string winTexture = "Img/winTexture.png", string fontFile = "Fonts/IndieFlower.ttf");
	
	bool setLv(int lv);

	int run();

	void draw(RenderWindow& window);

	~Play();
};