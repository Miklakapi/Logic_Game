#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class ShootingBlock : public RectangleShape{

	RectangleShape arrow;

	enum Direction {
		Up,
		Down,
		Left,
		Right
	};

public:
	
	ShootingBlock(Vector2f position, Direction direction);



};

