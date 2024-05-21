// GameObject.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameObject {
protected:
    sf::Shape *object;        // Непосредственно сам объект
    sf::Texture texture;              // Текстура объекта

    sf::Vector2f objectSize;

    int x;
    int y;

    bool b_selected;

public:
    // Конструктор с параметрами
    GameObject(int x, int y, sf::Vector2f size);

    // Деструктор
    ~GameObject();

    // Устанавливает текстуру
    void setTexture(const std::string& filename);

    // Отрисовка объекта
    void draw(sf::RenderWindow& window);

    // Возвращает 1, если объект под курсором и 0 - если нет
    bool isUnderCursor(int mouseX, int mouseY);

    bool isSelected();
    void clearSelection();
    void setSelection();
};