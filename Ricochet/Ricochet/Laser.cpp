#include "Laser.h"
#include <iostream>

Laser::Laser(sf::Vector2f gunPosition, sf::Vector2f vel) : velocity(0, 0) {
    // Установка начальных параметров лазера
    shape.setSize(sf::Vector2f(10, 10));       // Устанавливаем размеры лазера
    shape.setFillColor(sf::Color::Red);        // Устанавливаем цвет лазера
    shape.setPosition(gunPosition);            // Устанавливаем начальное положение лазера
    velocity = vel;                            // Устаналиваем вектор направления-скорости лазера
}

// Метод обновления положения лазера
void Laser::update() {
    // Обновляем положение лазера с учетом скорости
    shape.move(velocity);
    std::cout << "Laser position: " << shape.getPosition().x << " " << shape.getPosition().y << std::endl;
}

// Метод отрисовки лазера на экране
void Laser::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// Метод получения глобальных координат лазера
sf::Vector2f Laser::getPosition() const {
    return shape.getPosition();
}

// Метод задания нового вектора velocity лазера
void Laser::setVelocity(sf::Vector2f newVel) {
    velocity = newVel;
}

sf::Vector2f Laser::getReflectedVelocity(int reflectionAngle) {
    float newVelX, newVelY;

    /*if (reflectionAngle >= 0 && reflectionAngle < 90) {
        newVelX = cos(reflectionAngle);
        newVelY = sin(reflectionAngle);
    }
    else if (reflectionAngle >= 90 && reflectionAngle < 180) {
        newVelX = -cos(reflectionAngle);
        newVelY = sin(reflectionAngle);
    }
    else if (reflectionAngle >= 180 && reflectionAngle < 270) {
        newVelX = -cos(reflectionAngle);
        newVelY = -sin(reflectionAngle);
    }
    else if (reflectionAngle >= 270 && reflectionAngle <= 359) {
        newVelX = cos(reflectionAngle);
        newVelY = -sin(reflectionAngle);
    }*/

    return sf::Vector2f(newVelX, newVelY);
}


Laser::~Laser() {}
