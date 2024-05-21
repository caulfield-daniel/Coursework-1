// LaserGun.cpp
#include "LaserGun.h"


LaserGun::LaserGun(float x, float y, sf::Vector2f objectSize, sf::Vector2f vel) :
    GameObject(x, y, objectSize), laser(sf::Vector2f(x,y), vel), active(false) {

    delete object; // Освободим память от старой фигуры

    // Создаем объект
    object = new sf::CircleShape(objectSize.x / 2);
    object->setFillColor(sf::Color::Red);
    object->setOrigin(sf::Vector2f(objectSize.x / 2, objectSize.x / 2));
    object->setPosition(sf::Vector2f(x, y));
}

void LaserGun::update() {
    // Обновление состояния лазерного луча
    if (active) {
        laser.update();
    }
}

void LaserGun::setActive(bool activity) {
    active = activity;
}

bool LaserGun::isActive() const {
    return active;
}

void LaserGun::setVelocity(sf::Vector2f newVel) {
    laser.setVelocity(newVel);
}

sf::Vector2f LaserGun::getReflectedVelocity(int reflectionAngle) {
    return laser.getReflectedVelocity(reflectionAngle);
}

void LaserGun::drawLaser(sf::RenderWindow& window) {
    // Отрисовать лазерный луч
    laser.draw(window);
}

LaserGun::~LaserGun() {}



