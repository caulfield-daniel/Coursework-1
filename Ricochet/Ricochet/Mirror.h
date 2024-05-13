#pragma once
#include "RotatingObject.h"

class Mirror : public RotatingObject
{
public:
	Mirror();
	~Mirror();

	void create(int, int, sf::Vector2f);

	// Поворачивает объект влево на 30 градусов
	void rotateLeft();
	
	// Поворачивает объект вправо на 30 градусов
	void rotateRight();
};

