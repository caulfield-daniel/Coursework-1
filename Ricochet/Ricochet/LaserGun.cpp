#include "LaserGun.h"

LaserGun::LaserGun() {}

void LaserGun::create(int x, int y, sf::Vector2f s) {
	
	objectSize = s;
	mouseColliderSize = objectSize;

	// Создаем коллайдер
	mouseCollider.setSize(mouseColliderSize);
	mouseCollider.setFillColor(sf::Color(0, 255, 255, 0));
	mouseCollider.setOrigin(sf::Vector2f(objectSize.x / 2, objectSize.y / 2));
	mouseCollider.setPosition(sf::Vector2f(x, y));

	// Создаем объект
	object.setSize(objectSize);
	object.setFillColor(sf::Color::Red);
	object.setOrigin(sf::Vector2f(objectSize.x / 2, objectSize.y / 2));
	object.setPosition(sf::Vector2f(x, y));

}

LaserGun::~LaserGun() {}
