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
#include "Square2.hpp"

using namespace sf;
using namespace std;

class Screen{

public:

	enum Stage {
		NoneS,
		MapS,
		TargetS,
		BlocksS,
		SwitchS,
		Connection,
		SaveS
	};

	enum Click {
		NoneC,
		Teleport,
		Device
	};

private:

	Square2* squares;

	Texture* texture;

	CircleShape* shapes;

	CircleShape* shapes2;

	Screen::Stage stage;

public:

	Screen();

	void setStage(Screen::Stage stage);

	Screen::Stage getStage();

	void setContent(int number, Square2::MapStage content);

	void setContent(int number, Square2::TargetStage content);

	void setContent(int number, Square2::BlockStage content);

	void setContent(int number, Square2::BlockStage content, ShootingBlock::Type type);

	void setContent(int number, Square2::BlockStage content, LaserMachine::Type type);

	void setContent(int number, Square2::BlockStage content, Mirror::Type type);

	void setContent(int number, Square2::SwitchStage content, LaserReceiver::Type type = LaserReceiver::Type::A1);

	Square2::MapStage getMapS(int number);

	Square2::TargetStage getTargetS(int number);

	Square2::BlockStage getBlockS(int number);

	ShootingBlock::Type getShootingType(int number);

	LaserMachine::Type getLaserType(int number);

	Mirror::Type getMirrorType(int number);

	Square2::SwitchStage getSwitchS(int number);

	LaserReceiver::Type getReceiverType(int number);

	void setNewColor(int nr, Click clickType);

	void setColor(int number, Color color, Click clickType);

	Color getColor(int nr, Click clickType);

	bool findColor(Color color, Click clickType);

	void clearColor(Color color, Click clickType);

	void draw(RenderWindow& window);

	~Screen();

};