// Laser.h
#pragma once
#include <SFML/Graphics.hpp>

// ������ ��������� ����
class Laser {
private:
    sf::RectangleShape shape; // ����������� ������������� ������
    sf::Vector2f velocity;    // ������ �����������-�������� �������� ������
    sf::Vector2f direction;
    float speed;
    bool active;

public:
    Laser(sf::Vector2f gunPosition, float speed, sf::Vector2f direction);

    // ���������� ��������� ������
    void update();

    // ��������� ������ �� ������z
    void draw(sf::RenderWindow& window, int laserLength);

    // �������� ���������� ���������� ������
    sf::Vector2f getPosition() const;

    // ������ ����� ������ velocity
    void setVelocity(sf::Vector2f newVel);

    sf::Vector2f getVelocity();

    // �������� ������� ������� ������
    sf::FloatRect getGlobalBounds();

    // �������� ��������� ������ velocity �� ����������� �����
    sf::Vector2f getStartVelocity(const sf::Vector2f& gunDirection);

    // ������ ��������� ������
    void setPosition(sf::Vector2f newPosition);

    void setActive(bool activuty);

    // �������� ����� ������ velocity ����� ���������
    sf::Vector2f getReflectedVelocity(const sf::Vector2f& reflectionDirection);

    void setRotation(int angle);


    ~Laser();

};