#pragma once

#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include <fstream>
#include <string>

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

public:

	class HelpClass {

		int deviceNumber;

		string* deviceName;

		int* deviceID;

		bool* on;

	public:

		HelpClass();

		void setDeviceNumber(int number);

		int getDeviceNumber();

		void setDeviceName(int nr, string name);

		string getDeviceName(int nr);

		void setDeviceID(int nr, int id);

		int getDeviceID(int nr);

		void setOn(int nr, bool on);

		bool getOn(int nr);

		~HelpClass();
	};

private:

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

	VectorConverter startPosition;

	int seconds, minutes;

	Text winTime;

	Font font;

	HelpClass* receiverC;

	HelpClass* plateC;

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

public:
	
	Play(int lv, string loseTexture = "Img/loseTexture.png", string winTexture = "Img/winTexture.png", string fontFile = "Fonts/IndieFlower.ttf");
	
	void setLv(int lv);

	int run();

	void draw(RenderWindow& window);

	~Play();
};