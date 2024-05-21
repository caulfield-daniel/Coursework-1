#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

// Объект лазерного луча
class Laser {
private:
    sf::RectangleShape shape; // Графическое представление лазера
    sf::Vector2f velocity;    // Вектор направления-скорости движения лазера

public:
    Laser(sf::Vector2f gunPosition, sf::Vector2f vel);

    // Обновление положения лазера
    void update();

    // Отрисовка лазера на экране
    void draw(sf::RenderWindow& window);

    // Получить глобальные координаты лазера
    sf::Vector2f getPosition() const;

    // Задать новый вектор velocity
    void setVelocity(sf::Vector2f newVel);

    // Получить новый вектор velocity после отражения
    sf::Vector2f getReflectedVelocity(int reflectionAngle); 

    ~Laser();

};
