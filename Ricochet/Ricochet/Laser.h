// Laser.h
#pragma once
#include <SFML/Graphics.hpp>

// Объект лазерного луча
class Laser {
private:
    sf::RectangleShape shape; // Графическое представление лазера
    sf::Vector2f velocity;    // Вектор направления-скорости движения лазера
    sf::Vector2f direction;
    float speed;
    bool active;

public:
    Laser(sf::Vector2f gunPosition, float speed, sf::Vector2f direction);

    // Обновление положения лазера
    void update();

    // Отрисовка лазера на экранеz
    void draw(sf::RenderWindow& window, int laserLength);

    // Получить глобальные координаты лазера
    sf::Vector2f getPosition() const;

    // Задать новый вектор velocity
    void setVelocity(sf::Vector2f newVel);

    sf::Vector2f getVelocity();

    // Получить границы объекта лазера
    sf::FloatRect getGlobalBounds();

    // Получить начальный вектор velocity из направления пушки
    sf::Vector2f getStartVelocity(const sf::Vector2f& gunDirection);

    // Задать положение лазера
    void setPosition(sf::Vector2f newPosition);

    void setActive(bool activuty);

    // Получить новый вектор velocity после отражения
    sf::Vector2f getReflectedVelocity(const sf::Vector2f& reflectionDirection);

    void setRotation(int angle);


    ~Laser();

};