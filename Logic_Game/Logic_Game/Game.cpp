#include "Game.hpp"

Game::Game(RenderWindow& window){
	type = Type::InIntro;
	intro = new Intro;

	fstream stream;
	stream.open("settings.txt", ios::in);
	if (!stream.is_open()) {
		stream.open("settings.txt", ios::out);
		stream << "100";
		sound = true;
		fpsCounter = false;
		window.setFramerateLimit(60);
		stream.close();
	}
	else {
		string line;
		getline(stream, line);
		stream.close();
		for (int i = 0; i < 3; i++) {
			if (line.at(i) != '0' && line.at(i) != '1') {
				stream.open("settings.txt", ios::out);
				stream << "100";
				sound = true;
				fpsCounter = false;
				window.setFramerateLimit(60);
				stream.close();
			}
		}
		if (line.at(0) == '0') sound = false;
		else sound = true;
		if (line.at(1) == '0') {
			window.setFramerateLimit(60);
		}
		else {
			window.setFramerateLimit(144);
		}
		if (line.at(2) == '0') fpsCounter = false;
		else fpsCounter = true;
	}
	bufer.loadFromFile("Sound/click.ogg");
	clickSound.setBuffer(bufer);
	if (fpsCounter) FpsCounter = new FPS;
	delayClick.restart();
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
		Menu::Type type1 = menu->run(window, true);
		if (type1 == Menu::None);
		else if (type1 == Menu::Play && delayClick.getElapsedTime().asSeconds() > 0.2) {
			type = Type::InGame;
			levelSelect = new LevelSelect;
			if (sound) clickSound.play();
		}
		else if (type1 == Menu::Editor) {
			type = Type::InEditor;
			delete menu;
			editor = new Editor;
			if (sound) clickSound.play();
		}
		else if (type1 == Menu::Instruction) {
			instruction = new Instruction;
			type = Type::InInstruction;
			if (sound) clickSound.play();
		}
		else if (type1 == Menu::Options) {
			options = new Options(window);
			type = Type::InOptions;
			if (sound) clickSound.play();
		}
		else if (type1 == Menu::Exit && delayClick.getElapsedTime().asSeconds() > 0.2) {
			if (sound) clickSound.play();
			exit(0);
		}
	}
	else if (type == Type::InGame) {
		if (levelSelect->getType() != LevelSelect::Start) menu->run(window, false);
		LevelSelect::Type type1 = levelSelect->run(window);
		if (type1 == LevelSelect::Return) {
			type = Type::InMenu;
			delete levelSelect;
			delayClick.restart();
			if (sound) clickSound.play();
		}
		else if (type1 == LevelSelect::Start) {
			delete menu;
			if (sound) clickSound.play(); 
		}
		else if (type1 == LevelSelect::Exit) {
			type = Type::InMenu;
			delete levelSelect;
			menu = new Menu;
			delayClick.restart();
		}
	}
	else if (type == Type::InEditor) {
		if (editor->run(window) == Editor::Type::Exit) {
			delete editor;
			type = InMenu;
			menu = new Menu;
		}
	}
	else if (type == Type::InInstruction) {
		menu->run(window, false);
		if (instruction->run(window) == Instruction::Type::Return) {
			delete instruction;
			type = Type::InMenu;
			delayClick.restart();
			if (sound) clickSound.play();
		}
	}
	else if (type == Type::InOptions) {
		menu->run(window, false);
		if (options->run(window) == Options::Return) {
			type = Type::InMenu;
			this->sound = options->getSound();
			if (options->getCounter() && fpsCounter == false) {
				FpsCounter = new FPS;
				fpsCounter = true;
			}
			else if (!options->getCounter() && fpsCounter) {
				delete FpsCounter;
				fpsCounter = false;
			}
			delete options;
			delayClick.restart();
			if (sound) clickSound.play();
		}
	}

	if (fpsCounter) FpsCounter->run();
}

void Game::draw(RenderWindow& window) {
	switch (type) {
	case Type::InIntro:
		intro->draw(window);
		break;
	case Type::InMenu:
		menu->draw(window, true);
		break;
	case Type::InGame:
		levelSelect->draw(window);
		if (levelSelect->getType() != LevelSelect::Start) {
			menu->draw(window, false);
		}
		break;
	case Type::InEditor:
		editor->draw(window);
		break;
	case Type::InInstruction:
		instruction->draw(window);
		menu->draw(window, false);
		break;
	case Type::InOptions:
		options->draw(window);
		menu->draw(window, false);
		break;
	}
	if (fpsCounter) window.draw(*FpsCounter);
}

Game::~Game(){
	switch (type) {
	case Type::InIntro:
		delete intro;
		break;
	case Type::InMenu:
		delete menu;
		break;
	case Type::InGame:
		if (levelSelect->getType() != LevelSelect::Start) delete menu;
		delete levelSelect;
		break;
	case Type::InEditor:
		delete editor;
		break;
	case Type::InInstruction:
		delete instruction;
		delete menu;
		break;
	case Type::InOptions:
		delete menu;
		delete options;
		break;
	}
	if (fpsCounter) delete FpsCounter;
}