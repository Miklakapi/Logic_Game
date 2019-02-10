#pragma once
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Hearts{

	int health;

	RectangleShape* heart;

	static Texture* texture;

public:

	Hearts(Vector2f position = Vector2f{ 0,0 });

	static void loadTexture(string textureFile = "Img/Heart.png");

	void setTexture();

	void setPosition(Vector2f position);

	void setHealth(int health);

	int getHealth();

	void draw(RenderWindow& window);

	void reset();

	~Hearts();
};

