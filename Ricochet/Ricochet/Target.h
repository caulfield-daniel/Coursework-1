// Target.h
#pragma once
#include "GameObject.h"

class Target : public GameObject {
    bool hit;

public:
    Target(int x, int y, sf::Vector2f size);
    Target();
    ~Target();

    void destroy();

};