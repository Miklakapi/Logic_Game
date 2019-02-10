#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

class Data {

	int health;

	int lv;

	int minutes;

	int seconds;

public:

	int asHealth();

	int asLV();

	int asMinutes();

	int asSeconds();

	friend class MenuBar;
};