#include "RotatingObject.h"
#include <iostream>

RotatingObject::RotatingObject() {
	b_selected = false;
}


void RotatingObject::draw(sf::RenderWindow& window) {
	window.draw(mouseCollider);
	window.draw(object);
}

void RotatingObject::showMouseCollider(sf::RenderWindow& window) {
	mouseCollider.setFillColor(sf::Color(0, 255, 255, 100));
}

void RotatingObject::hideMouseCollider(sf::RenderWindow& window) {
	mouseCollider.setFillColor(sf::Color(0, 255, 255, 0));
}

void RotatingObject::create(int x1, int y1, sf::Vector2f s) {

	x = x1;
	y = y1;
	
	objectSize = s;
	mouseColliderSize = objectSize;

	// Создаем коллайдер
	mouseCollider.setSize(mouseColliderSize);
	mouseCollider.setFillColor(sf::Color(0, 255, 255, 0));
	mouseCollider.setOrigin(sf::Vector2f(objectSize.x / 2, objectSize.y / 2));
	mouseCollider.setPosition(sf::Vector2f(x1, y1));

	// Создаем объект
	object.setSize(objectSize);
	object.setFillColor(sf::Color::Green);
	object.setOrigin(sf::Vector2f(objectSize.x / 2, objectSize.y / 2));
	object.setPosition(sf::Vector2f(x1, y1));

}

bool RotatingObject::isUnderCursor(int mouseX, int mouseY) {
	bool isInside = mouseCollider.getGlobalBounds().contains(static_cast<float>(mouseX), static_cast<float>(mouseY));
	std::cout << "isUnderCursor called: " << isInside << std::endl;
	return isInside;
}



void RotatingObject::clearSelection()
{
	b_selected = false;
}
void RotatingObject::setSelection()
{
	b_selected = true;
}

bool RotatingObject::isSelected()
{
	return b_selected;
}

