#include <SFML/Graphics.hpp>
#include <iostream>
#include "RotatingObject.h"
#include "Mirror.h"
#include "LaserGun.h"

// Определяем количество зеркал и размеры окна
enum { MIRRORS_COUNT = 3 };
enum { WINDOW_HEIGHT = 480, WINDOW_WIDTH = 640 };

sf::Vector2f SIZE{ 10,60 };

int main()
{
    setlocale(LC_ALL, "RUS");
    
    // Создаем окно для игры
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ricochet");

    // Объявляем объекты игры
    Mirror mirror;
    LaserGun gun;
    RotatingObject obj;

    // Инициализируем объекты
    mirror.create(500, 210, SIZE);
    gun.create(200, 210, SIZE);
    obj.create(500, 360, SIZE);

    // Главный цикл игры
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            // Обработка событий

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

                // В главном цикле, при обработке события нажатия кнопки мыши

                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "Mouse unselected" << std::endl;
                }

                if (event.mouseButton.button == sf::Mouse::Left) {
                    int mouseX = sf::Mouse::getPosition(window).x;
                    int mouseY = sf::Mouse::getPosition(window).y;

                    std::cout << "Mouse X: " << mouseX << " Mouse Y: " << mouseY << std::endl;

                    // Проверяем, находился ли курсор над зеркалом в момент клика
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

        // Очищаем окно
        window.clear();

        // Рисуем объекты
        mirror.draw(window);
        gun.draw(window);
        obj.draw(window);

        // Отображаем содержимое окна
        window.display();
    }

    return 0;
}