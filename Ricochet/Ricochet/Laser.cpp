#include "Laser.h"
#include <iostream>

Laser::Laser(sf::Vector2f gunPosition, sf::Vector2f vel) : velocity(0, 0) {
    // ��������� ��������� ���������� ������
    shape.setSize(sf::Vector2f(10, 10));       // ������������� ������� ������
    shape.setFillColor(sf::Color::Red);        // ������������� ���� ������
    shape.setPosition(gunPosition);            // ������������� ��������� ��������� ������
    velocity = vel;                            // ������������ ������ �����������-�������� ������
}

// ����� ���������� ��������� ������
void Laser::update() {
    // ��������� ��������� ������ � ������ ��������
    shape.move(velocity);
    std::cout << "Laser position: " << shape.getPosition().x << " " << shape.getPosition().y << std::endl;
}

// ����� ��������� ������ �� ������
void Laser::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// ����� ��������� ���������� ��������� ������
sf::Vector2f Laser::getPosition() const {
    return shape.getPosition();
}

// ����� ������� ������ ������� velocity ������
void Laser::setVelocity(sf::Vector2f newVel) {
    velocity = newVel;
}

sf::Vector2f getReflectedVelocity(int reflectionAngle) {
    float newVelX, newVelY;

    if ((reflectionAngle >= 0 && reflectionAngle < 90) or
        (reflectionAngle >= 180 && reflectionAngle < 270)) {
        newVelX = cos(reflectionAngle);
        newVelY = sin(reflectionAngle);
    }
    else if (reflectionAngle >= 90 && reflectionAngle < 180) {
        newVelX = -cos(reflectionAngle);
        newVelY = sin(reflectionAngle);
    }
    else if (reflectionAngle >= 180 && reflectionAngle <= 270) {
        newVelX = -cos(reflectionAngle);
        newVelY = -sin(reflectionAngle);
    }
    else {
        newVelX = cos(reflectionAngle);
        newVelY = -sin(reflectionAngle);
    }

    return sf::Vector2f(newVelX, newVelY);
}



Laser::~Laser() {}