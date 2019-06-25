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

using namespace sf;
using namespace std;

class Square2 : public RectangleShape {

public:

	enum MapStage {
		Wall,
		Floor
	};

	enum TargetStage {
		NoneT,
		Start,
		Win
	};

	enum BlockStage {
		NoneB,
		SlidingBlock,
		TrapOn, TrapOff,
		DoorOn, DoorOff,
		TeleportOn, TeleportOff,
		ShootingBlockOn, ShootingBlockOff,
		EmiterOn, EmiterOff,
		Mirror
	};

	enum SwitchStage {
		NoneSw,
		Plate,
		Receiver
	};

private:

	MapStage element1;

	TargetStage element2;

	BlockStage element3;

	SwitchStage element4;

	LaserReceiver::Type type1;

	ShootingBlock::Type type2;

	LaserMachine::Type type3;

	Mirror::Type type4;

public:

	Square2();

	void setContent(MapStage content);

	void setContent(TargetStage content);

	void setContent(BlockStage content);

	void setContent(BlockStage content, ShootingBlock::Type type);

	void setContent(BlockStage content, LaserMachine::Type type);

	void setContent(BlockStage content, Mirror::Type type);

	void setContent(SwitchStage content, LaserReceiver::Type type = LaserReceiver::Type::A1);

	MapStage getMapS();

	TargetStage getTargetS();

	BlockStage getBlockS();

	ShootingBlock::Type getShootingType();

	LaserMachine::Type getLaserType();

	Mirror::Type getMirrorType();

	SwitchStage getSwitchS();

	LaserReceiver::Type getReceiverType();
};