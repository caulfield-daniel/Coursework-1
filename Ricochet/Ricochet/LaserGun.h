// LaserGun.h
#pragma once
#include "GameObject.h"
#include "Laser.h"

// ������ ��������� ������
class LaserGun : public GameObject {
private:
    bool active; // ������ ���������� ������
    sf::Vector2f direction; // ������ ����������� �����
    float angle; // ���� �������� ����� (� ��������) 
    class Laser* laser; // ������ ��������� ����

public:

    LaserGun(float x, float y, sf::Vector2f objectSize, float speed, float angle);

    LaserGun();

    // ������������ ����� ����� �� 30 ��������
    void rotateLeft();

    // ������������ ����� ������ �� 30 ��������
    void rotateRight();

    // ���������� ������� ������ ����������� �����
    sf::Vector2f getDirection() const;

    // ���������� ��������� ����
    void update();

    // ���������� ������ ���������� ������
    void setActive(bool active);

    // ���������, ������� �� ������
    bool isActive() const;

    // ������ ����� ������ velocity
    void setVelocity(sf::Vector2f newVel);

    // ������ ������� velocity
    sf::Vector2f getLaserVelocity() const;

    // ������ ������� ���� ��������
    int getRotationAngle() const;

    // �������� ������� ������� ������
    sf::FloatRect getLaserGlobalBounds() const;

    // �������� ����������� ������ velocity
    sf::Vector2f getStartVelocity(const sf::Vector2f& gunDirection);

    // �������� ����� ������ velocity ����� ���������
    sf::Vector2f getReflectedVelocity(const sf::Vector2f& reflectionDirection);

    // ������������ �����
    void reset();

    // ���������� �����
    void drawLaser(sf::RenderWindow& window, int laserLength);

    ~LaserGun();
};