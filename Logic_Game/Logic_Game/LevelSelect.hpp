#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "Play.hpp"

using namespace sf;
using namespace std;

class LevelSelect : public RectangleShape{

public:

	enum Type {
		None,
		Start,
		Exit,
		Return
	};

private:

	class Ring : public RectangleShape{
	
		bool complete;
	
	public:

		Ring();

		bool getComplete();

		void setComplete(bool complete);

		void draw(RenderWindow& window);
	};

	Texture texture;

	Texture ringTexture;

	Ring* ring;

	Play* play;

	Type type;

	Clock clickDelay;

public:

	LevelSelect();
	
	Type getType();

	Type run(RenderWindow& window);

	void draw(RenderWindow& window);

	~LevelSelect();
};