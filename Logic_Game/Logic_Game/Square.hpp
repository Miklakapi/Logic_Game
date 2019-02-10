#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

enum Type {
	Wall,
	Empty
};

class Square : public RectangleShape{

	Type type;

	static Texture* texture;

public:

	Square();

	static void setTextureFile(string textureFile = "Square.png");

	void setType(Type type);

	Type getType();

	void reset();
};

