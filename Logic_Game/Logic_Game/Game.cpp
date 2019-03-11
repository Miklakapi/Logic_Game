#include "Game.hpp"


Game::Game(){
	type = Type::InIntro;
	intro = new Intro;
}

void Game::run(RenderWindow& window) {
	if (type == Type::InIntro) {
		if (intro->run()) {
			type = Type::InMenu;
			delete intro;
			menu = new Menu;
		}
	}
	else if (type == Type::InMenu) {
		Menu::Type type1 = menu->run(window);
		if (type1 == Menu::None) return;
		else if (type1 == Menu::Play);
		else if (type1 == Menu::Editor);
		else if (type1 == Menu::Instruction);
		else if (type1 == Menu::Options) {

		}
		else if (type1 == Menu::Exit) exit(0);
	}
	else if (type == Type::InGame) {

	}
	else if (type == Type::InEditor) {

	}
	else if (type == Type::InInstruction) {

	}
	else if (type == Type::InOptions) {

	}
}

void Game::draw(RenderWindow& window) {
	switch (type) {
	case Type::InIntro:
		intro->draw(window);
		break;
	case Type::InMenu:
		menu->draw(window);
		break;
	case Type::InGame:

		break;
	case Type::InEditor:

		break;
	case Type::InInstruction:

		break;
	case Type::InOptions:
	
		break;
	}
}

Game::~Game(){
	delete menu;
}