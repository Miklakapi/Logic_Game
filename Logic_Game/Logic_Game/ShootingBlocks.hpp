#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "SlidingBLocks.hpp"

using namespace sf;
using namespace std;

class ShootingBlocks{

	ShootingBlock* block;

	int number;

public:

	ShootingBlocks(int number, string textureFile = "Img/ShootingBLock.png");



	~ShootingBlocks();
};

