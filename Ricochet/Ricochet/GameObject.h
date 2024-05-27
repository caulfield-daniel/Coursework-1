// GameObject.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class GameObject {
protected:
    sf::RectangleShape object;          // Базовый объект (коллайдер)
    sf::Sprite sprite;                  // Графическое представление объекта

    sf::Vector2f objectSize;

    int x;
    int y;
    bool b_selected;

public:
    // Конструктор по умолчанию
    GameObject();

    // Конструктор с параметрами
    GameObject(int x, int y, sf::Vector2f size);

    // Деструктор
    ~GameObject() = default;

    // Скрывает базовый объект (коллайдер)
    void hideCollider();

    void showCollider();

    // Отрисовка объекта
    void draw(sf::RenderWindow& window);

    // Установка текстуры объекта
    void setTexture(sf::Texture& texture, std::string filename);

    // Переместить объект в точку (posX, posY);
    void setPosition(int posX, int posY);

    // Задать угол поворота
    void setRotation(int angle);

    // Получить границы объекта
    sf::FloatRect getGlobalBounds() const;

    // Получить позицию
    sf::Vector2f getPosition() const;

    // Возвращает 1, если объект под курсором и 0 - если нет
    bool isUnderCursor(int mouseX, int mouseY);

    bool isSelected() const;
    void clearSelection();
    void setSelection();
};