#include "Mirror.h"

Mirror::Mirror() {}

void Mirror::create(int x2, int y2, sf::Vector2f s) {

	x = x2;
	y = y2;
	objectSize = s;
	mouseColliderSize = objectSize;
	

	// Создаем коллайдер
	mouseCollider.setSize(mouseColliderSize);
	mouseCollider.setFillColor(sf::Color(0, 255, 255, 0));
	mouseCollider.setOrigin(sf::Vector2f(objectSize.x / 2, objectSize.y / 2));
	mouseCollider.setPosition(sf::Vector2f(x2, y2));

	// Создаем объект
	object.setSize(objectSize);
	object.setFillColor(sf::Color(0, 238, 255, 255));
	object.setOrigin(sf::Vector2f(objectSize.x / 2, objectSize.y / 2));
	object.setPosition(sf::Vector2f(x2, y2));
}

void Mirror::rotateLeft() {
	object.rotate(-30.0f);
}

void Mirror::rotateRight() {
	object.rotate(30.0f);
}

Mirror::~Mirror() {}

