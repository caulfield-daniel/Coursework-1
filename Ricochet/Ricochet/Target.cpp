// Target.cpp
#include "Target.h"

Target::Target(int x, int y, sf::Vector2f objectSize)
    : GameObject(x, y, objectSize), isActive(true){

    object->setFillColor(sf::Color::Green);
}

void Target::destroy() {
    object->setFillColor(sf::Color::Red);
}

Target::~Target() {}