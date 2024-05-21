// Target.h
#pragma once
#include "GameObject.h"

class Target : public GameObject {
    bool isActive;
public:
    Target(int x, int y, sf::Vector2f size);
    ~Target();

    void destroy();
};