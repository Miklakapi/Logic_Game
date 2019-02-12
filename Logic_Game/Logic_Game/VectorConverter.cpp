#include "VectorConverter.hpp"

VectorConverter::VectorConverter(int number) {
	x = number - (18 * (number % 18));
	y = number % 18;
	this->number = number;
	vector = Vector2i{ int(x * 80),int(y * 80) };
}

VectorConverter::VectorConverter(int x, int y) {
	this->x = x;
	this->y = y;
	number = x + (y * 18);
	vector = Vector2i{ int(x * 80),int(y * 80) };
}

VectorConverter::VectorConverter(Vector2f vector) {
	this->vector = Vector2i{ int(vector.x),int(vector.y) };
	this->x = this->vector.x / 80;
	this->y = this->vector.y / 80;
	number = x + (y * 18);
}

VectorConverter::VectorConverter(Vector2i vector) {
	this->vector = vector;
	this->x = this->vector.x / 80;
	this->y = this->vector.y / 80;
	number = x + (y * 18);
}

VectorConverter::VectorConverter(Vector2u vector) {
	this->vector = Vector2i{ int(vector.x),int(vector.y) };
	this->x = this->vector.x / 80;
	this->y = this->vector.y / 80;
	number = x + (y * 18);
}

VectorConverter VectorConverter::convert(int number) {
	return VectorConverter(number);
}

VectorConverter VectorConverter::convert(int x, int y) {
	return VectorConverter(x, y);
}

int VectorConverter::asNumber() {
	return number;
}

Vector2i VectorConverter::asXY() {
	return Vector2i{ x,y };
}

Vector2f VectorConverter::asVector2f() {
	return Vector2f{ float(vector.x),float(vector.y) };
}

Vector2i VectorConverter::asVector2i() {
	return vector;
}

Vector2u VectorConverter::asVector2u() {
	return Vector2u{ unsigned int(vector.x),unsigned int(vector.y) };
}