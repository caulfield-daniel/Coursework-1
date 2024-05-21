// Mirror.cpp
#include "Mirror.h"

Mirror::Mirror(int x, int y, sf::Vector2f size, int angle) : 
    GameObject(x, y, size), angle(angle) {;
    object->rotate(-angle); 
    object->setFillColor(sf::Color(0, 238, 255, 255));
}


void Mirror::rotateLeft() {
    object->rotate(-30.0f);
    angle = (angle + 30) % 360; // В соответствии с тригонометрической окружностью
}

void Mirror::rotateRight() {
    object->rotate(30.0f);
    angle = (angle - 30) % 360; // В соответствии с тригонометрической окружностью
}

int Mirror::getAngle() {
    return angle;
}

void Mirror::setTexture(const std::string& filename) {
    GameObject::setTexture(filename);

}

Mirror::~Mirror() {}