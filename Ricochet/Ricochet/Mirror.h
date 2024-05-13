#pragma once
#include "RotatingObject.h"

class Mirror : public RotatingObject
{
public:
	Mirror();
	~Mirror();

	void create(int, int, sf::Vector2f);

	// ������������ ������ ����� �� 30 ��������
	void rotateLeft();
	
	// ������������ ������ ������ �� 30 ��������
	void rotateRight();
};

