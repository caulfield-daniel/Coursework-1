// GameObject.cpp
#include "GameObject.h"
#include <iostream>


GameObject::GameObject(int x, int y, sf::Vector2f size)
    : b_selected(false), x(x), y(y), objectSize(size) {

    // Создаем объект
    object = new sf::RectangleShape(objectSize);
    object->setFillColor(sf::Color::Green);
    object->setOrigin(sf::Vector2f(objectSize.x / 2, objectSize.y / 2));
    object->setPosition(sf::Vector2f(x, y));
}

void GameObject::setTexture(const std::string& filename) {
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Ошибка загрузки текстуры: " << filename << std::endl;
    }
    object->setTexture(&texture);
}

void GameObject::draw(sf::RenderWindow& window) {
    window.draw(*object);
}

bool GameObject::isUnderCursor(int mouseX, int mouseY) {
    object->getTransform();
    bool isInside = object->getGlobalBounds().contains(static_cast<float>(mouseX), static_cast<float>(mouseY));
    std::cout << "isUnderCursor called: " << isInside << std::endl;
    return isInside;
}

void GameObject::clearSelection() {
    b_selected = false;
}

void GameObject::setSelection() {
    b_selected = true;
}

bool GameObject::isSelected() {
    return b_selected;
}

GameObject::~GameObject() {
    delete object;
}