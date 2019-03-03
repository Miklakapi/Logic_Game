#include "HelpClass.hpp"

void HelpClass::move(Player& player, Map& map, SlidingBlock* block, int number, Mirror* mirror, int number2, Door* door, int number3,
	ShootingBlock* blockS, int number4, LaserMachine* machine, int number5) {

	Player::Direction direction = Player::None;
	if (Keyboard::isKeyPressed(Keyboard::W)) direction = Player::Up;
	else if (Keyboard::isKeyPressed(Keyboard::A)) direction = Player::Left;
	else if (Keyboard::isKeyPressed(Keyboard::S)) direction = Player::Down;
	else if (Keyboard::isKeyPressed(Keyboard::D)) direction = Player::Right;
	else return;


	if (player.movePlayer(direction, map, block, number, mirror, number2, door, number3, blockS, number4, machine, number5) && player.getLive()) {
		VectorConverter vec(player.getPosition());
		SlidingBlock::Direction direction1 = SlidingBlock::Up;
		VectorConverter vec2 = vec;
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			direction1 = SlidingBlock::Up;
			vec2 = VectorConverter::convert(vec.asXY().x, vec.asXY().y - 2);
			vec = VectorConverter::convert(vec.asXY().x, vec.asXY().y - 1);
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			direction1 = SlidingBlock::Left;
			vec2 = VectorConverter::convert(vec.asXY().x - 2, vec.asXY().y);
			vec = VectorConverter::convert(vec.asXY().x - 1, vec.asXY().y);
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			direction1 = SlidingBlock::Down;
			vec2 = VectorConverter::convert(vec.asXY().x, vec.asXY().y + 2);
			vec = VectorConverter::convert(vec.asXY().x, vec.asXY().y + 1);
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			direction1 = SlidingBlock::Right;
			vec2 = VectorConverter::convert(vec.asXY().x + 2, vec.asXY().y);
			vec = VectorConverter::convert(vec.asXY().x + 1, vec.asXY().y);
		}

		if (map.getType(vec2.asNumber()) == Square::Wall) return;
		
		int nr = -1;
		int nr2 = -1;

		for (int i = 0; i < number; i++) {
			if ((block + i)->getExist() && (block + i)->getPosition() == vec2.asVector2f()) return;
			if ((block + i)->getExist() && (block + i)->getPosition() == vec.asVector2f()) nr = i;
		}

		for (int i = 0; i < number2; i++) {
			if ((mirror + i)->getExist() && (mirror + i)->getPosition() == vec2.asVector2f()) return;
			if ((mirror + i)->getExist() && (mirror + i)->getPosition() == vec.asVector2f()) nr2 = i;
		}

		for (int i = 0; i < number3; i++) {
			if (!(door + i)->isOpen() && (door + i)->getPosition() == vec2.asVector2f()) return;
		}

		for (int i = 0; i < number4; i++) {
			if ((blockS + i)->getPosition() == vec2.asVector2f()) return;
		}

		for (int i = 0; i < number5; i++) {
			if ((machine + i)->getPosition() == vec2.asVector2f()) return;
		}

		if (nr != -1) {
			(block + nr)->push(direction1);
			return;
		}

		Mirror::Direction direction2 = Mirror::Up;
		if (Keyboard::isKeyPressed(Keyboard::W)) direction2 = Mirror::Up;
		else if (Keyboard::isKeyPressed(Keyboard::A)) direction2 = Mirror::Left;
		else if (Keyboard::isKeyPressed(Keyboard::S)) direction2 = Mirror::Down;
		else if (Keyboard::isKeyPressed(Keyboard::D)) direction2 = Mirror::Right;

		if (nr2 != -1) {
			(mirror + nr2)->push(direction2);
			return;
		}
	}
}

void HelpClass::runAll(Map& map, Player& player, SlidingBlocks& block, Mirrors& mirror, Doors& door, ShootingBlocks& blockS, LaserMachines& machine) {

}

void HelpClass::resetAll(Map& map, Player& player, SlidingBlocks& block, Mirrors& mirror, Doors& door, ShootingBlocks& blockS, LaserMachines& machine) {

}

void HelpClass::drawAll(RenderWindow& window, Map& map, Player& player, SlidingBlocks& block, Mirrors& mirror, Doors& door, ShootingBlocks& blockS, LaserMachines& machine) {

}