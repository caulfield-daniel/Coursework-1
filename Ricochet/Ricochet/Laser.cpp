#include "Laser.h"
#include <iostream>
#include "GameMath.h"

Laser::Laser(sf::Vector2f gunPosition, float speed, sf::Vector2f direction) : direction(direction), speed(speed), active(false) {
    // ��������� ��������� ���������� ������
    velocity = direction * speed;
    shape.setSize(sf::Vector2f(2,2));          // ������������� ������� ������
    shape.setOrigin(sf::Vector2f(1, 1));
    shape.setFillColor(sf::Color::Red); // ������������� ���� ������
    shape.setPosition(gunPosition);             // ������������� ��������� ��������� ������
}

// ����� ���������� ��������� ������
void Laser::update() {
    // ��������� ��������� ������ � ������ ��������
    shape.move(velocity*speed);
}

// ����� ��������� ������ �� ������
void Laser::draw(sf::RenderWindow& window, int laserLength) {
    if (active) {
        sf::VertexArray laserLine(sf::Lines, 2);    // ������� ���
        laserLine[0].position = shape.getPosition();
        laserLine[1].position = shape.getPosition() - sf::Vector2f(velocity.x * laserLength, velocity.y * laserLength); // ���������� ����� �� 100 ��������
        laserLine[0].color = sf::Color::Red;
        laserLine[1].color = sf::Color::Red;

        // ������������ ���
        window.draw(laserLine);
    }
}

// ����� ��������� ���������� ��������� ������
sf::Vector2f Laser::getPosition() const {
    return shape.getPosition();
}

void Laser::setPosition(sf::Vector2f newPosition) {
    shape.setPosition(newPosition);
}

// ����� ������� ������ ������� velocity ������
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
    // ����������� ������ ����������� �����
    sf::Vector2f direction = GameMath::normalize(gunDirection);

    // �������� ��������������� ����������� �� ��������� �������� ������
    return direction * speed;
}

sf::Vector2f Laser::getReflectedVelocity(const sf::Vector2f& reflectionDirection) {
    // ����������� ������ ����������� ���������
    sf::Vector2f reflection = GameMath::normalize(reflectionDirection);

    // ��������� ���������� ������ ��������
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