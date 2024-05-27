#include "Laser.h"
#include <iostream>
#include "GameMath.h"

Laser::Laser(sf::Vector2f gunPosition, float speed, sf::Vector2f direction) : direction(direction), speed(speed), active(false) {
    // Установка начальных параметров лазера
    velocity = direction * speed;
    shape.setSize(sf::Vector2f(2,2));          // Устанавливаем размеры лазера
    shape.setOrigin(sf::Vector2f(1, 1));
    shape.setFillColor(sf::Color::Red); // Устанавливаем цвет лазера
    shape.setPosition(gunPosition);             // Устанавливаем начальное положение лазера
}

// Метод обновления положения лазера
void Laser::update() {
    // Обновляем положение лазера с учетом скорости
    shape.move(velocity*speed);
}

// Метод отрисовки лазера на экране
void Laser::draw(sf::RenderWindow& window, int laserLength) {
    if (active) {
        sf::VertexArray laserLine(sf::Lines, 2);    // Создаем луч
        laserLine[0].position = shape.getPosition();
        laserLine[1].position = shape.getPosition() - sf::Vector2f(velocity.x * laserLength, velocity.y * laserLength); // Продолжаем линию на 100 пикселей
        laserLine[0].color = sf::Color::Red;
        laserLine[1].color = sf::Color::Red;

        // Отрисовываем луч
        window.draw(laserLine);
    }
}

// Метод получения глобальных координат лазера
sf::Vector2f Laser::getPosition() const {
    return shape.getPosition();
}

void Laser::setPosition(sf::Vector2f newPosition) {
    shape.setPosition(newPosition);
}

// Метод задания нового вектора velocity лазера
void Laser::setVelocity(sf::Vector2f newVel) {
    velocity = newVel;
}

sf::Vector2f Laser::getVelocity() {
    return velocity;
}

sf::FloatRect Laser::getGlobalBounds() {
    return shape.getGlobalBounds();
}

sf::Vector2f Laser::getStartVelocity(const sf::Vector2f& gunDirection) {
    // Нормализуем вектор направления пушки
    sf::Vector2f direction = GameMath::normalize(gunDirection);

    // Умножаем нормализованное направление на начальную скорость лазера
    return direction * speed;
}

sf::Vector2f Laser::getReflectedVelocity(const sf::Vector2f& reflectionDirection) {
    // Нормализуем вектор направления отражения
    sf::Vector2f reflection = GameMath::normalize(reflectionDirection);

    // Вычисляем отраженный вектор скорости
    float dotProduct = 2 * (velocity.x * reflection.x + velocity.y * reflection.y);
    float newX = velocity.x - dotProduct * reflection.x;
    float newY = velocity.y - dotProduct * reflection.y;

    return sf::Vector2f(newX, newY);
}

void Laser::setActive(bool activity) {
    active = activity;
}

void Laser::setRotation(int angle) {
    shape.setRotation(angle);
}

Laser::~Laser() {}