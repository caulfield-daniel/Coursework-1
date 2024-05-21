// Mirror.h
#pragma once
#include "GameObject.h"

class Mirror : public GameObject {
private:
    int angle;

public:
    Mirror(int x2, int y2, sf::Vector2f size, int angle);
    ~Mirror();

    // ������������ ������ ����� �� 30 ��������
    void rotateLeft();

    // ������������ ������ ������ �� 30 ��������
    void rotateRight();

    // ���������� ������� ���� �������� �������
    int getAngle();

    // ��������� �������� (����������� �� GameObject)
    void setTexture(const std::string& filename);
};