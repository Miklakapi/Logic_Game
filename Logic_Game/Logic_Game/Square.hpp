#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Square : public RectangleShape{

public:

	enum Type {
		Wall,
		Empty
	};

private:

	Square::Type type;

	static Texture* texture;

public:

	Square();

	static void setTextureFile(string textureFile = "Img/Square.png");

	void setType(Square::Type type);

	Square::Type getType();

	void reset();
};

