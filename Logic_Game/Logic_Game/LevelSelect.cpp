#include "LevelSelect.hpp"

LevelSelect::Ring::Ring(){
	complete = false;
}

bool LevelSelect::Ring::getComplete() {
	return complete;
}

void LevelSelect::Ring::setComplete(bool complete) {
	this->complete = complete;
}

void LevelSelect::Ring::draw(RenderWindow& window) {
	if(complete) window.draw(*this);
}

////////////////////////

LevelSelect::LevelSelect() {
	type = Type::None;
	setSize({ 1440,880 });
	texture.loadFromFile("Img/LevelSelect.png");
	setTexture(&texture);
	ringTexture.loadFromFile("Img/Ring.png");
	ring = new Ring[20];
	for (int i = 0; i < 20; i++) {
		(ring + i)->setTexture(&ringTexture);
		(ring + i)->setSize({ 113,113 });
	}
	(ring + 0)->setPosition({ 270,165 });
	(ring + 1)->setPosition({ 467,165 });
	(ring + 2)->setPosition({ 663,165 });
	(ring + 3)->setPosition({ 860,165 });
	(ring + 4)->setPosition({ 1057,165 });

	(ring + 5)->setPosition({ 270,308 });
	(ring + 6)->setPosition({ 467,308 });
	(ring + 7)->setPosition({ 663,308 });
	(ring + 8)->setPosition({ 860,308 });
	(ring + 9)->setPosition({ 1057,308 });

	(ring + 10)->setPosition({ 270,451 });
	(ring + 11)->setPosition({ 467,451 });
	(ring + 12)->setPosition({ 663,451 });
	(ring + 13)->setPosition({ 860,451 });
	(ring + 14)->setPosition({ 1057,451 });

	(ring + 15)->setPosition({ 270,594 });
	(ring + 16)->setPosition({ 467,594 });
	(ring + 17)->setPosition({ 663,594 });
	(ring + 18)->setPosition({ 860,594 });
	(ring + 19)->setPosition({ 1057,594 });

	fstream stream("Lvs/complete.txt", ios::in);
	if (!stream.is_open()) {
		stream.open("Lvs/complete.txt", ios::out);
		for (int i = 0; i < 20; i++) {
			stream << "false\n";
		}
		stream.close();
	}
	else {
		string line;
		for (int i = 0; i < 20; i++) {
			getline(stream, line);
			if (line == "true") {
				(ring + i)->setComplete(true);
			}
		}
		stream.close();
	}

}

LevelSelect::Type LevelSelect::getType() {
	return type;
}

LevelSelect::Type LevelSelect::run(RenderWindow& window) {

	if (type == None && Mouse::isButtonPressed(Mouse::Left)) {

		if (clickDelay.getElapsedTime().asSeconds() < 0.3) return Type::None;

		Vector2f pos = { float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y) };

		if (pos.x >= 495 && pos.x <= 945 && pos.y >= 737 && pos.y <= 850) {
			return Type::Return;
		}
		else if (pos.x > 270 && pos.x < 383) {
			if (pos.y > 165 && pos.y < 278) {
				play = new Play(1);
				type = Type::Start;
			}
			else if (pos.y > 308 && pos.y < 421) {
				play = new Play(6);
				type = Type::Start;
			}
			else if (pos.y > 451 && pos.y < 564) {
				play = new Play(11);
				type = Type::Start;
			}
			else if (pos.y > 594 && pos.y < 707) {
				play = new Play(16);
				type = Type::Start;
			}
		}
		else if (pos.x > 467 && pos.x < 580) {
			if (pos.y > 165 && pos.y < 278) {
				play = new Play(2);
				type = Type::Start;
			}
			else if (pos.y > 308 && pos.y < 421) {
				play = new Play(7);
				type = Type::Start;
			}
			else if (pos.y > 451 && pos.y < 564) {
				play = new Play(12);
				type = Type::Start;
			}
			else if (pos.y > 594 && pos.y < 707) {
				play = new Play(17);
				type = Type::Start;
			}
		}
		else if (pos.x > 663 && pos.x < 776) {
			if (pos.y > 165 && pos.y < 278) {
				play = new Play(3);
				type = Type::Start;
			}
			else if (pos.y > 308 && pos.y < 421) {
				play = new Play(8);
				type = Type::Start;
			}
			else if (pos.y > 451 && pos.y < 564) {
				play = new Play(13);
				type = Type::Start;
			}
			else if (pos.y > 594 && pos.y < 707) {
				play = new Play(18);
				type = Type::Start;
			}
		}
		else if (pos.x > 860 && pos.x < 973) {
			if (pos.y > 165 && pos.y < 278) {
				play = new Play(4);
				type = Type::Start;
			}
			else if (pos.y > 308 && pos.y < 421) {
				play = new Play(9);
				type = Type::Start;
			}
			else if (pos.y > 451 && pos.y < 564) {
				play = new Play(14);
				type = Type::Start;
			}
			else if (pos.y > 594 && pos.y < 707) {
				play = new Play(19);
				type = Type::Start;
			}
		}
		else if (pos.x > 1057 && pos.x < 1170) {
			if (pos.y > 165 && pos.y < 278) {
				play = new Play(5);
				type = Type::Start;
			}
			else if (pos.y > 308 && pos.y < 421) {
				play = new Play(10);
				type = Type::Start;
			}
			else if (pos.y > 451 && pos.y < 564) {
				play = new Play(15);
				type = Type::Start;
			}
			else if (pos.y > 594 && pos.y < 707) {
				play = new Play(20);
				type = Type::Start;
			}
		}
		if (type == Type::Start) return Type::Start;

		return Type::None;
	}

	if (type == Type::Start) {
		int nr = play->run();
		if (nr != -1) {

			if (nr == 0) { // Game Over
				return Type::Exit;
			}
			else if (nr > 0) { // Level complete

				fstream stream("Lvs/complete.txt", ios::in);
				if (!stream.is_open()) {
					stream.open("Lvs/complete.txt", ios::out);
					for (int i = 0; i < 20; i++) {
						stream << "false\n";
					}
					stream.close();
				}
				else {
					string* line = new string[20];
					for (int i = 0; i < 20; i++) {
						getline(stream, *(line + i));
						if ((i + 1) == nr) *(line + i) = "true";
					}
					stream.close();

					stream.open("Lvs/complete.txt", ios::out);
					for (int i = 0; i < 20; i++) {
						stream << *(line + i);
						stream << '\n';
					}

					delete [] line;
					stream.close();
				}
				return Type::Exit;
			}

		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		if(type == Type::Start) return Type::Exit;
		else if (type == Type::None) return Type::Return;
	}
	return Type::None;
}

void LevelSelect::draw(RenderWindow& window) {
	if (type == None) {
		window.draw(*this);
		for (int i = 0; i < 20; i++) {
			(ring + i)->draw(window);
		}
	}
	else {
		play->draw(window);
	}
}

LevelSelect::~LevelSelect(){
	if (type == Type::Start) delete play;
	delete [] ring;
}