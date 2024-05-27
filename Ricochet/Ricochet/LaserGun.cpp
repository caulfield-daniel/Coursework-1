// LaserGun.cpp
#include "LaserGun.h"
#include <SFML/Graphics.hpp>
#include "GameMath.h"

LaserGun::LaserGun(float x, float y, sf::Vector2f objectSize, float speed, float angle) :
    GameObject(x, y, objectSize), active(false),
    direction(GameMath::getDirectionFromAngle(angle)),
    angle(angle), laser(nullptr) {

    // Создаем лазер
    laser = new Laser(sf::Vector2f(x, y), speed, direction);

    // Создаем пушку
    object.setRotation(-angle);
    sprite.setRotation(-angle);
    object.setFillColor(sf::Color::Transparent);
}

LaserGun::LaserGun() : GameObject(), active(false),
direction(1.0f, 0.0f), angle(0), laser(nullptr) {
    // Создаем лазер
    laser = new Laser(sf::Vector2f(x, y), 0, direction);

    // Создаем пушку
    object.setRotation(-angle);
    sprite.setRotation(-angle);
    object.setFillColor(sf::Color::Transparent);
}

void LaserGun::rotateLeft() {
    angle = std::fmod(angle - 30, 360); // В соответствии с тригонометрической окружностью
    direction = GameMath::normalize(GameMath::getDirectionFromAngle(angle));
}

void LaserGun::rotateRight() {
    angle = std::fmod(angle + 30, 360); // В соответствии с тригонометрической окружностью
    direction = GameMath::normalize(GameMath::getDirectionFromAngle(angle));
}

int LaserGun::getRotationAngle() const {
    return angle;
}

sf::Vector2f LaserGun::getDirection() const {
    return direction;
}

sf::Vector2f LaserGun::getLaserVelocity() const {
    return laser->getVelocity();
}

void LaserGun::update() {
    object.setRotation(angle);
    laser->setRotation(angle);
    sprite.setRotation(angle);

    // Обновление состояния лазерного луча
    if (active) {
        laser->setActive(true);
        laser->update();
    }
    else {
        laser->setActive(false);
    }
}

void LaserGun::setActive(bool activity) {
    active = activity;
}

bool LaserGun::isActive() const {
    return active;
}

void LaserGun::setVelocity(sf::Vector2f newVel) {
    laser->setVelocity(newVel);
}

sf::Vector2f LaserGun::getStartVelocity(const sf::Vector2f& gunDirection) {
    return laser->getStartVelocity(gunDirection);
}

sf::Vector2f LaserGun::getReflectedVelocity(const sf::Vector2f& reflectionDirection) {
    return laser->getReflectedVelocity(reflectionDirection);
}

sf::FloatRect LaserGun::getLaserGlobalBounds() const {
    return laser->getGlobalBounds();
}

void LaserGun::reset() {
    if (laser) {
        // Перемещаем лазер в исходное положение
        laser->setPosition(object.getPosition());
        laser->setVelocity(getStartVelocity(direction));
        active = false;
    }
}

void LaserGun::drawLaser(sf::RenderWindow& window, int laserLength) {
    // Отрисовать лазерный луч
    if (laser)
        laser->draw(window, laserLength);
}

LaserGun::~LaserGun() {
    delete laser;
}