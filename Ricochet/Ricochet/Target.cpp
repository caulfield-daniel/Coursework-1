// Target.cpp
#include "Target.h"
#include <SFML/Graphics.hpp>

Target::Target(int x, int y, sf::Vector2f objectSize)
    : GameObject(x, y, objectSize), hit(false) {

    object.setFillColor(sf::Color::Transparent);
    object.setScale(0.7, 0.7);
}

Target::Target() : GameObject(), hit(false) {
    object.setFillColor(sf::Color::Transparent);
    object.setScale(0.7, 0.7);
}

void Target::destroy() {
    hit = true;
    sprite.setColor(sf::Color::Transparent);
}

Target::~Target() {}
