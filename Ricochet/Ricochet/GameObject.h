// GameObject.h
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameObject {
protected:
    sf::Shape *object;        // ��������������� ��� ������
    sf::Texture texture;              // �������� �������

    sf::Vector2f objectSize;

    int x;
    int y;

    bool b_selected;

public:
    // ����������� � �����������
    GameObject(int x, int y, sf::Vector2f size);

    // ����������
    ~GameObject();

    // ������������� ��������
    void setTexture(const std::string& filename);

    // ��������� �������
    void draw(sf::RenderWindow& window);

    // ���������� 1, ���� ������ ��� �������� � 0 - ���� ���
    bool isUnderCursor(int mouseX, int mouseY);

    bool isSelected();
    void clearSelection();
    void setSelection();
};