// Mirror.h
#pragma once
#include "GameObject.h"

class Mirror : public GameObject {
private:
    sf::Vector2f direction; // Вектор направления зеркала
    float angle; // Угол поворота зеркала (в градусах)

public:
    Mirror(int x2, int y2, sf::Vector2f size, float angle);
    Mirror();
    ~Mirror();

    // Поворачивает объект влево на 30 градусов
    void rotateLeft();

    // Поворачивает объект вправо на 30 градусов
    void rotateRight();
    
    // Узнать текущий угол поворота
    int getRotationAngle() const;

    // Возвращает текущий вектор направления зеркала
    sf::Vector2f getDirection() const;

    // Обновление состояния
    void update();

};