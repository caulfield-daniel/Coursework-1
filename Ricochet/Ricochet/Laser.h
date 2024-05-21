#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

// ������ ��������� ����
class Laser {
private:
    sf::RectangleShape shape; // ����������� ������������� ������
    sf::Vector2f velocity;    // ������ �����������-�������� �������� ������

public:
    Laser(sf::Vector2f gunPosition, sf::Vector2f vel);

    // ���������� ��������� ������
    void update();

    // ��������� ������ �� ������
    void draw(sf::RenderWindow& window);

    // �������� ���������� ���������� ������
    sf::Vector2f getPosition() const;

    // ������ ����� ������ velocity
    void setVelocity(sf::Vector2f newVel);

    // �������� ����� ������ velocity ����� ���������
    sf::Vector2f getReflectedVelocity(int reflectionAngle); 

    ~Laser();

};
