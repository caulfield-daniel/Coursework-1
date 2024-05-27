// Mirror.h
#pragma once
#include "GameObject.h"

class Mirror : public GameObject {
private:
    sf::Vector2f direction; // ������ ����������� �������
    float angle; // ���� �������� ������� (� ��������)

public:
    Mirror(int x2, int y2, sf::Vector2f size, float angle);
    Mirror();
    ~Mirror();

    // ������������ ������ ����� �� 30 ��������
    void rotateLeft();

    // ������������ ������ ������ �� 30 ��������
    void rotateRight();
    
    // ������ ������� ���� ��������
    int getRotationAngle() const;

    // ���������� ������� ������ ����������� �������
    sf::Vector2f getDirection() const;

    // ���������� ���������
    void update();

};