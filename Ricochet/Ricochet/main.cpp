#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.h"
#include "Mirror.h"
#include "LaserGun.h"
#include "Target.h"
#include <cmath>

// Определяем количество зеркал и размеры окна
enum { MIRRORS_COUNT = 3 };
enum { WINDOW_HEIGHT = 480, WINDOW_WIDTH = 640 };

sf::Vector2f SIZE{ 50, 100 };


int main()
{
    setlocale(LC_ALL, "RUS");
    
    // Создаем окно для игры
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ricochet");

    // Cоздеам фон
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    background.setFillColor(sf::Color(100, 100, 100));

    // Создаем игровые объекты
    Mirror mirror(300, 100, SIZE, 0);
    LaserGun gun(100, 100, SIZE, sf::Vector2f(0.001, 0));
    gun.setVelocity(gun.getReflectedVelocity(mirror.getAngle()));
    Target t1(150, 300, SIZE);

    mirror.setTexture("C:\\Users\\1\\source\\repos\\Ricochet\\Ricochet\\Assets\\mirror.png");
    
    // Главный цикл игры
    while (window.isOpen()) {

        // Обновляем положение лазера каждую итерацию цикла
        gun.update();

        sf::Event event; {
            while (window.pollEvent(event)) {

                // Обработка событий
                switch (event.type) {

                case sf::Event::Closed: {
                    window.close();
                    break;
                }

                case sf::Event::MouseButtonPressed: {

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int mouseX = sf::Mouse::getPosition(window).x;
                        int mouseY = sf::Mouse::getPosition(window).y;

                        std::cout << "Mouse X: " << mouseX << " Mouse Y: " << mouseY << std::endl;

                        // Проверяем, находился ли курсор над зеркалом в момент клика
                        if (mirror.isUnderCursor(mouseX, mouseY)) {
                            mirror.setSelection();
                            std::cout << "Mirror selected" << std::endl;
                        }

                        else {
                            mirror.clearSelection();
                            std::cout << "Mirror unselected" << std::endl;
                        }

                        break;
                    }

                case sf::Event::KeyPressed: {

                    if (event.key.code == sf::Keyboard::Space) {
                        if (!gun.isActive()) {
                            gun.setActive(true);
                        }
                        else {
                            gun.setActive(false);
                        }
                        std::cout << "LaserGun activated: " << gun.isActive() << std::endl;
                    }

                    if (mirror.isSelected()) {

                        if (event.key.code == sf::Keyboard::Right) {
                            mirror.rotateRight();
                        }

                        if (event.key.code == sf::Keyboard::Left) {
                            mirror.rotateLeft();
                        }

                        std::cout << "Rotation angle: " << mirror.getAngle() << std::endl;

                    }

                }
                                          break;
                }

                }
            }
        }

        // Очищаем окно
        window.clear();

        // Рисуем фон
        window.draw(background);

        // Рисуем объекты
        mirror.draw(window);
        gun.draw(window);
        gun.drawLaser(window);
        t1.draw(window);

        // Отображаем содержимое окна
        window.display();
    }

    return 0;
}