#include "Options.hpp"

Options::Options(RenderWindow& window){
	setSize({ 1440,880 });

	for (int i = 0; i < 2; i++) {
		sound[i].setSize({ 113,113 });
		fps[i].setSize({ 113,113 });
		counter[i].setSize({ 113,113 });
	}

	fstream stream;
	stream.open("settings.txt", ios::in);
	if (!stream.is_open()) {
		stream.open("settings.txt", ios::out);
		stream << "100";
		bSound = true;
		iFps = 60;
		bCounter = false;
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
				bSound = true;
				iFps = 60;
				bCounter = false;
				window.setFramerateLimit(60);
				stream.close();
			}
		}
		if (line.at(0) == '0') bSound = false;
		else bSound = true;
		if (line.at(1) == '0') {
			iFps = 60;
			window.setFramerateLimit(60);
		}
		else {
			iFps = 144;
			window.setFramerateLimit(144);
		}
		if (line.at(2) == '0') bCounter = false;
		else bCounter = true;
	}

	//

	texture = new Texture[5];
	(texture + 0)->loadFromFile("Img/Options.png");
	(texture + 1)->loadFromFile("Img/ON.png");
	(texture + 2)->loadFromFile("Img/OFF.png");
	(texture + 3)->loadFromFile("Img/60.png");
	(texture + 4)->loadFromFile("Img/144.png");

	//

	setTexture((texture + 0));
	
	sound[0].setTexture((texture + 2));
	sound[1].setTexture((texture + 1));

	fps[0].setTexture((texture + 3));
	fps[1].setTexture((texture + 4));

	counter[0].setTexture((texture + 2));
	counter[1].setTexture((texture + 1));

	//

	sound[0].setPosition({ 382,165 });
	sound[1].setPosition({ 945,165 });

	fps[0].setPosition({ 382,308 });
	fps[1].setPosition({ 945,308 });

	counter[0].setPosition({ 382,451 });
	counter[1].setPosition({ 945,451 });

	//

	IntRect rect[2]{ {0,0,113,113}, {113,0,113,113} };

	if (bSound) {
		sound[0].setTextureRect(rect[0]);
		sound[1].setTextureRect(rect[1]);
	}
	else {
		sound[1].setTextureRect(rect[0]);
		sound[0].setTextureRect(rect[1]);
	}

	if (bCounter) {
		counter[0].setTextureRect(rect[0]);
		counter[1].setTextureRect(rect[1]);
	}
	else {
		counter[1].setTextureRect(rect[0]);
		counter[0].setTextureRect(rect[1]);
	}

	if (iFps == 60) {
		fps[1].setTextureRect(rect[0]);
		fps[0].setTextureRect(rect[1]);
	}
	else {
		fps[0].setTextureRect(rect[0]);
		fps[1].setTextureRect(rect[1]);
	}
}

bool Options::getSound() {
	return bSound;
}

int Options::getFps() {
	return iFps;
}

bool Options::getCounter() {
	return bCounter;
}

Options::Type Options::run(RenderWindow& window) {

	if (Mouse::isButtonPressed(Mouse::Left) && clickDelay.getElapsedTime().asSeconds() >= 0.2) {
		clickDelay.restart();
		Vector2f pos = { float(Mouse::getPosition(window).x), float(Mouse::getPosition(window).y) };
		IntRect rect[2]{ {0,0,113,113}, {113,0,113,113} };

			if (pos.x >= 495 && pos.x <= 945) {

				if (pos.y >= 737 && pos.y <= 850) {
					fstream stream;
					stream.open("settings.txt", ios::out);

					if (bSound) stream << 1;
					else stream << 0;

					if (iFps == 60) {
						window.setFramerateLimit(60);
						stream << 0;
					}
					else {
						window.setFramerateLimit(144);
						stream << 1;
					}

					if (bCounter) stream << 1;
					else stream << 0;
						
					return Type::Return;
				}
			}
			else if (pos.x >= 385 && pos.x <= 490) {
				if (pos.y >= 170 && pos.y <= 273) {
					bSound = false;
					sound[1].setTextureRect(rect[0]);
					sound[0].setTextureRect(rect[1]);
				}
				else if (pos.y >= 303 && pos.y <= 416) {
					iFps = 60;
					fps[1].setTextureRect(rect[0]);
					fps[0].setTextureRect(rect[1]);
				}
				else if (pos.y >= 446 && pos.y <= 560) {
					bCounter = false;
					counter[1].setTextureRect(rect[0]);
					counter[0].setTextureRect(rect[1]);
				}
			}
			else if (pos.x >= 950 && pos.x <= 1053) {
				if (pos.y >= 170 && pos.y <= 273) {
					bSound = true;
					sound[0].setTextureRect(rect[0]);
					sound[1].setTextureRect(rect[1]);
				}
				else if (pos.y >= 303 && pos.y <= 416) {
					iFps = 144;
					fps[0].setTextureRect(rect[0]);
					fps[1].setTextureRect(rect[1]);
				}
				else if (pos.y >= 446 && pos.y <= 560) {
					bCounter = true;
					counter[0].setTextureRect(rect[0]);
					counter[1].setTextureRect(rect[1]);
				}
			}
	}

	return None;
}

void Options::draw(RenderWindow& window) {
	window.draw(*this);
	for (int i = 0; i < 2; i++) {
		window.draw(sound[i]);
		window.draw(fps[i]);
		window.draw(counter[i]);
	}
}

Options::~Options() {
	delete [] texture;
}