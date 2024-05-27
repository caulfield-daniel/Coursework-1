// LaserGun.h
#pragma once
#include "GameObject.h"
#include "Laser.h"

// Объект источника лазера
class LaserGun : public GameObject {
private:
    bool active; // Статус активности оружия
    sf::Vector2f direction; // Вектор направления пушки
    float angle; // Угол поворота пушки (в градусах) 
    class Laser* laser; // Объект лазерного луча

public:

    LaserGun(float x, float y, sf::Vector2f objectSize, float speed, float angle);

    LaserGun();

    // Поворачивает пушку влево на 30 градусов
    void rotateLeft();

    // Поворачивает пушку вправо на 30 градусов
    void rotateRight();

    // Возвращает текущий вектор направления пушки
    sf::Vector2f getDirection() const;

    // Обновление лазерного луча
    void update();

    // Установить статус активности оружия
    void setActive(bool active);

    // Проверить, активно ли оружие
    bool isActive() const;

    // Задать новый вектор velocity
    void setVelocity(sf::Vector2f newVel);

    // Узнать текущее velocity
    sf::Vector2f getLaserVelocity() const;

    // Узнать текущий угол поворота
    int getRotationAngle() const;

    // Получить границы объекта лазера
    sf::FloatRect getLaserGlobalBounds() const;

    // Получить изначальный вектор velocity
    sf::Vector2f getStartVelocity(const sf::Vector2f& gunDirection);

    // Получить новый вектор velocity после отражения
    sf::Vector2f getReflectedVelocity(const sf::Vector2f& reflectionDirection);

    // Перезарядить лазер
    void reset();

    // Отрисовать лазер
    void drawLaser(sf::RenderWindow& window, int laserLength);

    ~LaserGun();
};