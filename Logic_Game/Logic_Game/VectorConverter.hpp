#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;

class VectorConverter{

	int number;

	int x;

	int y;

	Vector2i vector;

public:

	VectorConverter(int number);

	VectorConverter(int x, int y);

	VectorConverter(Vector2f vector);

	VectorConverter(Vector2i vector);

	VectorConverter(Vector2u vector);
	
	static VectorConverter convert(int number);

	static VectorConverter convert(int x, int y);

	int asNumber();

	Vector2i asXY();

	Vector2f asVector2f();

	Vector2i asVector2i();

	Vector2u asVector2u();

};

