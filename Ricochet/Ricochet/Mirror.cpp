// Mirror.cpp
#include "Mirror.h"
#include "GameMath.h"
#include <SFML/Graphics.hpp>

Mirror::Mirror(int x, int y, sf::Vector2f size, float angle) :
    GameObject(x, y, size), angle(angle), direction(cos(angle* (3.1415926535f / 180.f)), sin(angle* (3.1415926535f / 180.f))) {

    sprite.setRotation(-angle);
    object.setRotation(-angle);
    object.setFillColor(sf::Color::Transparent);
    /*object.setSize(sf::Vector2f(objectSize.x*0.3, objectSize.y));*/
    object.setScale(0.1, 1);
    sprite.setScale(1.0, 1.0);
}

Mirror::Mirror() : GameObject(), angle(0), direction(1.0f, 0.0f) {
    sprite.setRotation(-angle);
    object.setRotation(-angle);
    object.setFillColor(sf::Color::Transparent);
}

void Mirror::rotateLeft() {
    angle = std::fmod(angle - 30, 360); // В соответствии с тригонометрической окружностью
    direction = GameMath::normalize(GameMath::getDirectionFromAngle(angle));
}

void Mirror::rotateRight() {
    angle = std::fmod(angle + 30, 360); // В соответствии с тригонометрической окружностью
    direction = GameMath::normalize(GameMath::getDirectionFromAngle(angle));
}

int Mirror::getRotationAngle() const {
    return angle;
}

sf::Vector2f Mirror::getDirection() const {
    return direction;
}

void Mirror::update() {
    object.setRotation(angle);
    sprite.setRotation(angle);
}

Mirror::~Mirror() {}
