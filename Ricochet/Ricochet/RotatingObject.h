#pragma once
#include <SFML/Graphics.hpp>

class RotatingObject
{
protected:
	sf::RenderWindow* window;		// ��������� �� ����, ����� ��� ���������
	sf::RectangleShape mouseCollider;	// ��������� ��� �������������� ������� � �����
	sf::RectangleShape object;		// ��������������� ��� ������

	sf::Vector2f objectSize;
	sf::Vector2f mouseColliderSize;			

	int x;
	int y;

	bool b_selected;


public:
	// ����������� �� ���������
	RotatingObject();

	// C������� ������� � �������� ��������� � �������
	void create(int, int, sf::Vector2f);

	~RotatingObject() {};

	// ���������� ��������� ��� ����
	void showMouseCollider(sf::RenderWindow& window);	

	// �������� ��������� ��� ����
	void hideMouseCollider(sf::RenderWindow& window);		

	// ������ ������������� ������� objectSize
	void draw(sf::RenderWindow& window);	

	// ������������� ���������� ������	
	void setNewPos(int, int);		
	
	// ���������� 1, ���� ������ ��� �������� � 0 - ���� ���
	bool isUnderCursor(int, int);

	bool isSelected();
	void clearSelection();
	void setSelection();

};