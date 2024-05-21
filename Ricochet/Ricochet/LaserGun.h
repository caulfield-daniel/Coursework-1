// LaserGun.h
#pragma once
#include "GameObject.h"
#include "Laser.h"

// ������ ��������� ������
class LaserGun : public GameObject {
private:
    bool active; // ������ ���������� ������
    Laser laser;   // ������ ��������� ����

public:
    LaserGun(float x, float y, sf::Vector2f size, sf::Vector2f vel);

    // ���������� ��������� ����
    void update();

    // ���������� ������ ���������� ������
    void setActive(bool active);

    // ���������, ������� �� ������
    bool isActive() const;

    // ������ ����� ������ velocity
    void setVelocity(sf::Vector2f newVel);

    // �������� ����� ������ velocity ����� ���������
    sf::Vector2f getReflectedVelocity(int reflectionAngle);

    // ���������� �����
    void drawLaser(sf::RenderWindow& window);

    ~LaserGun();
};

