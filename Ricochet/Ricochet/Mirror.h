// Mirror.h
#pragma once
#include "GameObject.h"

class Mirror : public GameObject {
private:
    int angle;

public:
    Mirror(int x2, int y2, sf::Vector2f size, int angle);
    ~Mirror();

    // Поворачивает объект влево на 30 градусов
    void rotateLeft();

    // Поворачивает объект вправо на 30 градусов
    void rotateRight();

    // Возвращает текущий угол поворота зеркала
    int getAngle();

    // Установка текстуры (наследуется от GameObject)
    void setTexture(const std::string& filename);
};