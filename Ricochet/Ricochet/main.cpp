#include <SFML/Graphics.hpp>
#include <iostream>
#include "RotatingObject.h"
#include "Mirror.h"
#include "LaserGun.h"

// ���������� ���������� ������ � ������� ����
enum { MIRRORS_COUNT = 3 };
enum { WINDOW_HEIGHT = 480, WINDOW_WIDTH = 640 };

sf::Vector2f SIZE{ 10,60 };

int main()
{
    setlocale(LC_ALL, "RUS");
    
    // ������� ���� ��� ����
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ricochet");

    // ��������� ������� ����
    Mirror mirror;
    LaserGun gun;
    RotatingObject obj;

    // �������������� �������
    mirror.create(500, 210, SIZE);
    gun.create(200, 210, SIZE);
    obj.create(500, 360, SIZE);

    // ������� ���� ����
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            // ��������� �������

            switch (event.type) {
            case sf::Event::Closed: {
                window.close();
                break;
            }

            case sf::Event::MouseButtonPressed: {

                if (event.mouseButton.button == sf::Mouse::Right) {
                    mirror.clearSelection();
                    std::cout << "mirror unselected" << std::endl;
                }

                // � ������� �����, ��� ��������� ������� ������� ������ ����

                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Mouse unselected" << std::endl;
                }

                if (event.mouseButton.button == sf::Mouse::Left) {
                    int mouseX = sf::Mouse::getPosition(window).x;
                    int mouseY = sf::Mouse::getPosition(window).y;

                    std::cout << "Mouse X: " << mouseX << " Mouse Y: " << mouseY << std::endl;

                    // ���������, ��������� �� ������ ��� �������� � ������ �����
                    if (mirror.isUnderCursor(mouseX, mouseY)) {
                        mirror.setSelection();
                        std::cout << "Mirror selected" << std::endl;
                    }

                break;
            }

            case sf::Event::KeyPressed: {

                if (event.key.code == sf::Keyboard::S) {
                    mirror.showMouseCollider(window);
                }

                if (event.key.code == sf::Keyboard::H) {
                    mirror.hideMouseCollider(window);
                }

                if (mirror.isSelected()) {

                    if (event.key.code == sf::Keyboard::Right) {
                        mirror.rotateRight();
                    }

                    if (event.key.code == sf::Keyboard::Left) {
                        mirror.rotateLeft();
                    }

                }

            }
                break;
            }

            }
        }

        // ������� ����
        window.clear();

        // ������ �������
        mirror.draw(window);
        gun.draw(window);
        obj.draw(window);

        // ���������� ���������� ����
        window.display();
    }

    return 0;
}