// GameObject.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class GameObject {
protected:
    sf::RectangleShape object;          // ������� ������ (���������)
    sf::Sprite sprite;                  // ����������� ������������� �������

    sf::Vector2f objectSize;

    int x;
    int y;
    bool b_selected;

public:
    // ����������� �� ���������
    GameObject();

    // ����������� � �����������
    GameObject(int x, int y, sf::Vector2f size);

    // ����������
    ~GameObject() = default;

    // �������� ������� ������ (���������)
    void hideCollider();

    void showCollider();

    // ��������� �������
    void draw(sf::RenderWindow& window);

    // ��������� �������� �������
    void setTexture(sf::Texture& texture, std::string filename);

    // ����������� ������ � ����� (posX, posY);
    void setPosition(int posX, int posY);

    // ������ ���� ��������
    void setRotation(int angle);

    // �������� ������� �������
    sf::FloatRect getGlobalBounds() const;

    // �������� �������
    sf::Vector2f getPosition() const;

    // ���������� 1, ���� ������ ��� �������� � 0 - ���� ���
    bool isUnderCursor(int mouseX, int mouseY);

    bool isSelected() const;
    void clearSelection();
    void setSelection();
};