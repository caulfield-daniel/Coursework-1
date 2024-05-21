// LaserGun.h
#pragma once
#include "GameObject.h"
#include "Laser.h"

// Объект источника лазера
class LaserGun : public GameObject {
private:
    bool active; // Статус активности оружия
    Laser laser;   // Объект лазерного луча

public:
    LaserGun(float x, float y, sf::Vector2f size, sf::Vector2f vel);

    // Обновление лазерного луча
    void update();

    // Установить статус активности оружия
    void setActive(bool active);

    // Проверить, активно ли оружие
    bool isActive() const;

    // Задать новый вектор velocity
    void setVelocity(sf::Vector2f newVel);

    // Получить новый вектор velocity после отражения
    sf::Vector2f getReflectedVelocity(int reflectionAngle);

    // Отрисовать лазер
    void drawLaser(sf::RenderWindow& window);

    ~LaserGun();
};

