#include "Editor.hpp"

Editor::Editor(){
	stage = Screen::Stage::MapS;
	screen = new Screen[4];
	(screen + 0)->setStage(Screen::Stage::MapS);
	(screen + 1)->setStage(Screen::Stage::TargetS);
	(screen + 2)->setStage(Screen::Stage::BlocksS);
	(screen + 3)->setStage(Screen::Stage::SwitchS);
	delayClock.restart();
}

Editor::Type Editor::run(RenderWindow& window) {

	if (delayClock.getElapsedTime().asSeconds() >= 0.2) {
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			return Type::Exit;
		}
		else if (Keyboard::isKeyPressed(Keyboard::A)) {
			delayClock.restart();
			if (stage == Screen::Stage::TargetS) stage = Screen::Stage::MapS;
			else if (stage == Screen::Stage::BlocksS) stage = Screen::Stage::TargetS;
			else if (stage == Screen::Stage::SwitchS) stage = Screen::Stage::BlocksS;
		}
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			delayClock.restart();
			if (stage == Screen::Stage::MapS) stage = Screen::Stage::TargetS;
			else if (stage == Screen::Stage::TargetS) stage = Screen::Stage::BlocksS;
			else if (stage == Screen::Stage::BlocksS) stage = Screen::Stage::SwitchS;
			else if (stage == Screen::Stage::SwitchS) stage = Screen::Stage::SaveS;
		}
	}

	if (delayClock.getElapsedTime().asSeconds() < 0.15) return Type::None;

	if (stage == Screen::Stage::MapS) {

	/*	if (Mouse::isButtonPressed(Mouse::Left)) {

		}
		else if (Mouse::isButtonPressed(Mouse::Right)) {

		}
		else if (Mouse::isButtonPressed(Mouse::Middle)) {

		}*/
		/////////////////
		/////////////////
		/////////////////

	}
	else if (stage == Screen::Stage::TargetS){

		/////////////////
		/////////////////
		/////////////////
	}
	else if (stage == Screen::Stage::BlocksS) {

		/////////////////
		/////////////////
		/////////////////
	}
	else if (stage == Screen::Stage::SwitchS) {

		/////////////////
		/////////////////
		/////////////////
	}


	return Type::None;
}

void Editor::draw(RenderWindow& window) {
	if (stage == Screen::Stage::MapS) {
		(screen + 0)->draw(window);
	}
	else if (stage == Screen::Stage::TargetS) {
		(screen + 0)->draw(window);
		(screen + 1)->draw(window);
	}
	else if (stage == Screen::Stage::BlocksS) {
		(screen + 0)->draw(window);
		(screen + 1)->draw(window);
		(screen + 2)->draw(window);
	}
	else if (stage == Screen::Stage::SwitchS) {
		(screen + 0)->draw(window);
		(screen + 1)->draw(window);
		(screen + 2)->draw(window);
		(screen + 3)->draw(window);
	}
	else if (stage == Screen::Stage::SaveS) {
		/////////////////
		/////////////////
		/////////////////
	}
}

Editor::~Editor(){
	delete [] screen;
}