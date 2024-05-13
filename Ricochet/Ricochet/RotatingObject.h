#pragma once
#include <SFML/Graphics.hpp>

class RotatingObject
{
protected:
	sf::RenderWindow* window;		// Указатель на окно, нужен для отрисовки
	sf::RectangleShape mouseCollider;	// Коллайдер для взаимодействия объекта с мышью
	sf::RectangleShape object;		// Непосредственно сам объект

	sf::Vector2f objectSize;
	sf::Vector2f mouseColliderSize;			

	int x;
	int y;

	bool b_selected;


public:
	// Конструктор по умолчанию
	RotatingObject();

	// Cоздание обьекта с заданием координат и размера
	void create(int, int, sf::Vector2f);

	~RotatingObject() {};

	// Отображает коллайдер для мыши
	void showMouseCollider(sf::RenderWindow& window);	

	// Скрывает коллайдер для мыши
	void hideMouseCollider(sf::RenderWindow& window);		

	// Рисует прямоугольник размера objectSize
	void draw(sf::RenderWindow& window);	

	// Устанавливает координаты центра	
	void setNewPos(int, int);		
	
	// Возвращает 1, если объект под курсором и 0 - если нет
	bool isUnderCursor(int, int);

	bool isSelected();
	void clearSelection();
	void setSelection();

};