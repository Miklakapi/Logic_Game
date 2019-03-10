#include "HelpClass.hpp"

void HelpClass::move(Player& player, Map& map, SlidingBlock* block, int number, Mirror* mirror, int number2, Door* door, int number3,
	ShootingBlock* blockS, int number4, LaserMachine* machine, int number5) {

	bool end(false);

	Player::Direction direction = Player::None;
	if (Keyboard::isKeyPressed(Keyboard::W)) direction = Player::Up;
	else if (Keyboard::isKeyPressed(Keyboard::A)) direction = Player::Left;
	else if (Keyboard::isKeyPressed(Keyboard::S)) direction = Player::Down;
	else if (Keyboard::isKeyPressed(Keyboard::D)) direction = Player::Right;
	else end = true;


	if (player.movePlayer(direction, map, block, number, mirror, number2, door, number3, blockS, number4, machine, number5) && player.getLive() && end == false) {
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

		if (map.getType(vec2.asNumber()) == Square::Wall) end = true;
		
		int nr = -1;
		int nr2 = -1;

		for (int i = 0; i < number && end == false; i++) {
			if ((block + i)->getExist() && (block + i)->getPosition() == vec2.asVector2f()) {
				end = true;
				break;
			}
			if ((block + i)->getExist() && (block + i)->getPosition() == vec.asVector2f()) nr = i;
		}

		for (int i = 0; i < number2 && end == false; i++) {
			if ((mirror + i)->getExist() && (mirror + i)->getPosition() == vec2.asVector2f()) {
				end = true;
				break;
			}
			if ((mirror + i)->getExist() && (mirror + i)->getPosition() == vec.asVector2f()) nr2 = i;
		}

		for (int i = 0; i < number3 && end == false; i++) {
			if (!(door + i)->isOpen() && (door + i)->getPosition() == vec2.asVector2f()) {
				end = true;
				break;
			}
		}

		for (int i = 0; i < number4 && end == false; i++) {
			if ((blockS + i)->getPosition() == vec2.asVector2f()) {
				end = true;
				break;
			}
		}

		for (int i = 0; i < number5 && end == false; i++) {
			if ((machine + i)->getPosition() == vec2.asVector2f()) {
				end = true;
				break;
			}
		}

		if (end == false) {
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
				end = true;
			}
		}
	}
	player.run(blockS, number4);
}

void HelpClass::runAll(MenuBar& menu, Map& map, TeleportFields& fields, Plates& plates, Traps& traps, Player& player, SlidingBlocks& block, Mirrors& mirror, Doors& door, ShootingBlocks& blockS, LaserMachines& machine) {
	menu.run();
	plates.run(player, block.getBlock(), block.getNumber(), mirror.getMirror(), mirror.getNumber());
	fields.run(player, block.getBlock(), block.getNumber(), mirror.getMirror(), mirror.getNumber());
	block.run();
	mirror.run(map,block.getBlock(),block.getNumber(),door.getDoor(),door.getNumber(),blockS.getBlock(),blockS.getNumber(),machine.getMachine(), machine.getNumber());
	traps.run(player, block.getBlock(), block.getNumber(), mirror.getMirror(), mirror.getNumber());
	machine.run(block.getBlock(), block.getNumber(), mirror.getMirror(), mirror.getNumber(), door.getDoor(), door.getNumber());
	blockS.run(map, door.getDoor(), door.getNumber(), block.getBlock(), block.getNumber(), mirror.getMirror(), mirror.getNumber(), machine.getMachine(), machine.getNumber());
}

void HelpClass::resetAll(MenuBar& menu, Map& map, Player& player, SlidingBlocks& block, Mirrors& mirror, Doors& door, ShootingBlocks& blockS, LaserMachines& machine) {
	map.reset();
	player.reset();
	block.reset();
	mirror.reset();
	door.reset();
	blockS.reset();
	machine.reset();
	menu.reset();
}

void HelpClass::drawAll(RenderWindow& window, MenuBar& menu, Map& map, TeleportFields& fields, Plates& plates,Traps& traps, Player& player, SlidingBlocks& block, Mirrors& mirror, Doors& door, ShootingBlocks& blockS, LaserMachines& machine) {
	map.draw(window);
	fields.draw(window);
	plates.draw(window);
	traps.draw(window);
	player.draw(window);
	block.draw(window);
	mirror.draw(window);
	door.draw(window);
	blockS.draw(window);
	machine.draw(window);
	menu.draw(window);
}