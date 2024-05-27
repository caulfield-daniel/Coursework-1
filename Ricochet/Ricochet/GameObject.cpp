#include "GameObject.h"

// Конструктор по умолчанию
GameObject::GameObject() :
    object(sf::Vector2f(0, 0)),
    sprite(),
    objectSize(0, 0),
    x(0),
    y(0),
    b_selected(false)
{
    object.setFillColor(sf::Color(100, 100, 100, 255));
    object.setOutlineThickness(5);
    object.setOutlineColor(sf::Color(100, 100, 100, 0));
    object.setScale(0.5, 0.5);
}

// Конструктор с параметрами
GameObject::GameObject(int x, int y, sf::Vector2f size) :
    object(size),
    sprite(),
    objectSize(size),
    x(x),
    y(y),
    b_selected(false)
{
    object.setPosition(x, y);
    object.setFillColor(sf::Color(100, 100, 100, 255));
    object.setOutlineThickness(5);
    object.setOutlineColor(sf::Color(100, 100, 100, 0));
    object.setScale(0.5, 0.5);
    sprite.setPosition(x, y);
}

// Скрывает базовый объект (коллайдер)
void GameObject::hideCollider() {
    object.setFillColor(sf::Color(0, 0, 0, 0));
    object.setOutlineThickness(0);
}

// Показать объект
void GameObject::showCollider() {
    object.setFillColor(sf::Color(100, 100, 100, 255));
    object.setOutlineColor(sf::Color(50, 50, 50, 255));
    object.setOutlineThickness(5);
}

// Отрисовка объекта
void GameObject::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(object);
}

// Установка текстуры объекта
void GameObject::setTexture(sf::Texture& texture, std::string filename) {
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Ошибка загрузки текстуры: " << filename << std::endl;
    }
    sf::Vector2u textureSize = texture.getSize();

    sprite.setTexture(texture);
    sprite.setOrigin(textureSize.x / 2, textureSize.y / 2);
    object.setOrigin(textureSize.x / 2, textureSize.y / 2);
}

// Переместить объект в точку (posX, posY);
void GameObject::setPosition(int posX, int posY) {
    x = posX;
    y = posY;
    object.setPosition(x, y);
    sprite.setPosition(x, y);
}

void GameObject::setRotation(int angle) {
    object.setRotation(-angle);
}


// Получить границы объекта
sf::FloatRect GameObject::getGlobalBounds() const {
    return object.getGlobalBounds();
}

// Получить позицию
sf::Vector2f GameObject::getPosition() const {
    return sf::Vector2f(x, y);
}

// Возвращает 1, если объект под курсором и 0 - если нет
bool GameObject::isUnderCursor(int mouseX, int mouseY) {
    return object.getGlobalBounds().contains(mouseX, mouseY);
}

bool GameObject::isSelected() const {
    return b_selected;
}

void GameObject::clearSelection() {
    b_selected = false;
}

void GameObject::setSelection() {
    b_selected = true;
}