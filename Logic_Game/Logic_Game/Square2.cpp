#include "Square2.hpp"

Square2::Square2() {
	setSize(Vector2f{ 80,80 });
}

void Square2::setContent(MapStage content) {
	element1 = content;
	if (content == MapStage::Wall) {
		setTextureRect(IntRect{ 0,0,80,80 });
	}
	else {
		setTextureRect(IntRect{ 80,0,80,80 });
	}
}

void Square2::setContent(TargetStage content) {
	element2 = content;
	if (content == TargetStage::Start) {
		setTextureRect(IntRect{ 80,0,80,80 });
	}
	else if (content == TargetStage::Win) {
		setTextureRect(IntRect{ 0,0,80,80 });
	}
	else {
		setTextureRect(IntRect{ 80,0,1,1 });
	}
}

void Square2::setContent(BlockStage content) {
	element3 = content;
	
	if (content == BlockStage::NoneB) {
		setTextureRect(IntRect{ 250,100,1,1 });
	}
	else if (content == BlockStage::SlidingBlock) {
		setTextureRect(IntRect{ 240,0,80,80 });
	}
	else if (content == BlockStage::TrapOff) {
		setTextureRect(IntRect{ 0,0,80,80 });
	}
	else if (content == BlockStage::TrapOn) {
		setTextureRect(IntRect{ 0,80,80,80 });
	}
	else if (content == BlockStage::DoorOff) {
		setTextureRect(IntRect{ 80,0,80,80 });
	}
	else if (content == BlockStage::DoorOn) {
		setTextureRect(IntRect{ 80,80,80,80 });
	}
	else if (content == BlockStage::TeleportOff) {
		setTextureRect(IntRect{ 160,0,80,80 });
	}
	else if (content == BlockStage::TeleportOn) {
		setTextureRect(IntRect{ 160,80,80,80 });
	}
}

void Square2::setContent(BlockStage content, ShootingBlock::Type type) {
	element3 = content;
	type2 = type;

	IntRect* shootingRect = new IntRect[15];

	if (content == BlockStage::ShootingBlockOn) {
		*(shootingRect + 0) = { 0,0,80,80 };
		*(shootingRect + 1) = { 80,0,80,80 };
		*(shootingRect + 2) = { 160,0,80,80 };
		*(shootingRect + 3) = { 240,0,80,80 };
		*(shootingRect + 4) = { 0,80,80,80 };
		*(shootingRect + 5) = { 80,80,80,80 };
		*(shootingRect + 6) = { 160,80,80,80 };
		*(shootingRect + 7) = { 240,80,80,80 };
		*(shootingRect + 8) = { 320,80,80,80 };
		*(shootingRect + 9) = { 400,80,80,80 };
		*(shootingRect + 10) = { 0,160,80,80 };
		*(shootingRect + 11) = { 80,160,80,80 };
		*(shootingRect + 12) = { 160,160,80,80 };
		*(shootingRect + 13) = { 240,160,80,80 };
		*(shootingRect + 14) = { 0,240,80,80 };

		setTextureRect(*(shootingRect + type));
	}
	else if (content == BlockStage::ShootingBlockOff) {
		*(shootingRect + 0) = { 480,0,80,80 };
		*(shootingRect + 1) = { 560,0,80,80 };
		*(shootingRect + 2) = { 640,0,80,80 };
		*(shootingRect + 3) = { 720,0,80,80 };
		*(shootingRect + 4) = { 480,80,80,80 };
		*(shootingRect + 5) = { 560,80,80,80 };
		*(shootingRect + 6) = { 640,80,80,80 };
		*(shootingRect + 7) = { 720,80,80,80 };
		*(shootingRect + 8) = { 800,80,80,80 };
		*(shootingRect + 9) = { 880,80,80,80 };
		*(shootingRect + 10) = { 480,160,80,80 };
		*(shootingRect + 11) = { 560,160,80,80 };
		*(shootingRect + 12) = { 640,160,80,80 };
		*(shootingRect + 13) = { 720,160,80,80 };
		*(shootingRect + 14) = { 800,240,80,80 };

		setTextureRect(*(shootingRect + type));
	}

	delete [] shootingRect;
}

void Square2::setContent(BlockStage content, LaserMachine::Type type) {
	element3 = content;
	type3 = type;

	IntRect* laserRect = new IntRect[15];

	if (content == BlockStage::EmiterOn) {
		*(laserRect + 0) = { 0,0,80,80 };
		*(laserRect + 1) = { 80,0,80,80 };
		*(laserRect + 2) = { 160,0,80,80 };
		*(laserRect + 3) = { 240,0,80,80 };
		*(laserRect + 4) = { 0,80,80,80 };
		*(laserRect + 5) = { 80,80,80,80 };
		*(laserRect + 6) = { 160,80,80,80 };
		*(laserRect + 7) = { 240,80,80,80 };
		*(laserRect + 8) = { 320,80,80,80 };
		*(laserRect + 9) = { 400,80,80,80 };
		*(laserRect + 10) = { 0,160,80,80 };
		*(laserRect + 11) = { 80,160,80,80 };
		*(laserRect + 12) = { 160,160,80,80 };
		*(laserRect + 13) = { 240,160,80,80 };
		*(laserRect + 14) = { 0,240,80,80 };

		setTextureRect(*(laserRect + type));
	}
	else if (content == BlockStage::EmiterOff) {
		*(laserRect + 0) = { 480,0,80,80 };
		*(laserRect + 1) = { 560,0,80,80 };
		*(laserRect + 2) = { 640,0,80,80 };
		*(laserRect + 3) = { 720,0,80,80 };
		*(laserRect + 4) = { 480,80,80,80 };
		*(laserRect + 5) = { 560,80,80,80 };
		*(laserRect + 6) = { 640,80,80,80 };
		*(laserRect + 7) = { 720,80,80,80 };
		*(laserRect + 8) = { 800,80,80,80 };
		*(laserRect + 9) = { 880,80,80,80 };
		*(laserRect + 10) = { 480,160,80,80 };
		*(laserRect + 11) = { 560,160,80,80 };
		*(laserRect + 12) = { 640,160,80,80 };
		*(laserRect + 13) = { 720,160,80,80 };
		*(laserRect + 14) = { 800,240,80,80 };

		setTextureRect(*(laserRect + type));
	}

	delete[] laserRect;
}

void Square2::setContent(BlockStage content, Mirror::Type type) {
	element3 = content;
	type4 = type;

	IntRect* mirrorRect = new IntRect[9];

	*(mirrorRect + 0) = { 0,0,80,80 };
	*(mirrorRect + 1) = { 80,0,80,80 };
	*(mirrorRect + 2) = { 160,0,80,80 };
	*(mirrorRect + 3) = { 240,0,80,80 };
	*(mirrorRect + 4) = { 0,80,80,80 };
	*(mirrorRect + 5) = { 80,80,80,80 };
	*(mirrorRect + 6) = { 160,80,80,80 };
	*(mirrorRect + 7) = { 240,80,80,80 };
	*(mirrorRect + 8) = { 0,160,80,80 };

	setTextureRect(*(mirrorRect + type));

	delete[] mirrorRect;
}

void Square2::setContent(SwitchStage content, LaserReceiver::Type type) {
	element4 = content;
	if (content == SwitchStage::Plate) {
		setTextureRect(IntRect{ 0,0,80,80 });
	}
	else if (content == SwitchStage::Receiver) {
		IntRect* receiverRect = new IntRect[30];
		*(receiverRect + 0) = { 0, 0, 80, 80 };
		*(receiverRect + 1) = { 80, 0, 80, 80 };
		*(receiverRect + 2) = { 160, 0, 80, 80 };
		*(receiverRect + 3) = { 240, 0, 80, 80 };

		*(receiverRect + 4) = { 0, 80, 80, 80 };
		*(receiverRect + 5) = { 80, 80, 80, 80 };
		*(receiverRect + 6) = { 160, 80, 80, 80 };
		*(receiverRect + 7) = { 240, 80, 80, 80 };
		*(receiverRect + 8) = { 320, 80, 80, 80 };
		*(receiverRect + 9) = { 400, 80, 80, 80 };

		*(receiverRect + 10) = { 0, 160, 80, 80 };
		*(receiverRect + 11) = { 80, 160, 80, 80 };
		*(receiverRect + 12) = { 160, 160, 80, 80 };
		*(receiverRect + 13) = { 240, 160, 80, 80 };

		*(receiverRect + 14) = { 0, 320, 80, 80 };

		*(receiverRect + 15) = { 480, 0, 80, 80 };
		*(receiverRect + 16) = { 560, 0, 80, 80 };
		*(receiverRect + 17) = { 640, 0, 80, 80 };
		*(receiverRect + 18) = { 720, 0, 80, 80 };

		*(receiverRect + 19) = { 480, 80, 80, 80 };
		*(receiverRect + 20) = { 560, 80, 80, 80 };
		*(receiverRect + 21) = { 640, 80, 80, 80 };
		*(receiverRect + 22) = { 720, 80, 80, 80 };
		*(receiverRect + 23) = { 800, 80, 80, 80 };
		*(receiverRect + 24) = { 880, 80, 80, 80 };

		*(receiverRect + 25) = { 480, 160, 80, 80 };
		*(receiverRect + 26) = { 560, 160, 80, 80 };
		*(receiverRect + 27) = { 640, 160, 80, 80 };
		*(receiverRect + 28) = { 720, 160, 80, 80 };

		*(receiverRect + 29) = { 480, 320, 80, 80 };

		setTextureRect(*(receiverRect + type));

		this->type1 = type;

		delete[] receiverRect;
	}
	else {
		setTextureRect(IntRect{ 3,3,1,1 });
	}
}

Square2::MapStage Square2::getMapS() {
	return element1;
}

Square2::TargetStage Square2::getTargetS() {
	return element2;
}

Square2::BlockStage Square2::getBlockS() {
	return element3;
}

ShootingBlock::Type Square2::getShootingType() {
	return type2;
}

LaserMachine::Type Square2::getLaserType() {
	return type3;
}

Mirror::Type Square2::getMirrorType() {
	return type4;
}

Square2::SwitchStage Square2::getSwitchS() {
	return element4;
}

LaserReceiver::Type Square2::getReceiverType() {
	return type1;
}