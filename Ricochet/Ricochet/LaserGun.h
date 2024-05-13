#pragma once
#include "RotatingObject.h"

class LaserGun : public RotatingObject
{
public:
	LaserGun();
	~LaserGun();

	void create(int, int, sf::Vector2f);
};

