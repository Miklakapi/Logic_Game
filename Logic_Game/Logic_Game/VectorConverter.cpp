#include "VectorConverter.hpp"

VectorConverter::VectorConverter(int number) {
	y = int(number / 18);
	x = number % 18;
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
	this->x = vector.x / 80;
	this->y = vector.y / 80;
	number = x + (y * 18);
	this->vector = Vector2i{ int(x * 80),int(y * 80) };
}

VectorConverter::VectorConverter(Vector2i vector) {
	this->x = vector.x / 80;
	this->y = vector.y / 80;
	number = x + (y * 18);
	this->vector = Vector2i{ int(x * 80),int(y * 80) };
}

VectorConverter::VectorConverter(Vector2u vector) {
	this->x = vector.x / 80;
	this->y = vector.y / 80;
	number = x + (y * 18);
	this->vector = Vector2i{ int(x * 80),int(y * 80) };
}

VectorConverter VectorConverter::convert(int number) {
	return VectorConverter(number);
}

VectorConverter VectorConverter::convert(int x, int y) {
	return VectorConverter(x, y);
}

VectorConverter VectorConverter::convert(Vector2f vector) {
	return VectorConverter(vector);
}

VectorConverter VectorConverter::convert(Vector2i vector) {
	return VectorConverter(vector);
}

VectorConverter VectorConverter::convert(Vector2u vector) {
	return VectorConverter(vector);
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