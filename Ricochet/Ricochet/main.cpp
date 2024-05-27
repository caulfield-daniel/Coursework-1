#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.h"
#include "Mirror.h"
#include "LaserGun.h"
#include "Target.h"
#include "GameMath.h"
#include <vector>
#include <random>
#include "LevelGenerator.h"
#include <filesystem>
#include <fstream>

// ���������
const int MIRRORS_COUNT = 5;
const int TARGETS_COUNT = 3;

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 600;

const sf::Vector2f SIZE(100, 100);

// ���� � ��������� (�������������)
const std::filesystem::path MIRROR_TEXTURE_PATH = "Assets/mirror.png";
const std::filesystem::path GUN_TEXTURE_PATH = "Assets/lasergun.png";
const std::filesystem::path TARGET_TEXTURE_PATH = "Assets/target.png";
const std::filesystem::path BACKGROUND_TEXTURE_PATH = "Assets/background.png";

// ������� ��� �������� ��������
sf::Texture loadTexture(const std::filesystem::path& path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path.string())) {
        std::cerr << "������ �������� ��������: " << path.string() << std::endl;
    }
    return texture;
}

int main() {
    // ������� ����
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ricochet");

    // ������� ��� � ���������
    sf::RectangleShape background(sf::Vector2f(WINDOW_HEIGHT, WINDOW_WIDTH));
    sf::Texture backgroundTexture = loadTexture(BACKGROUND_TEXTURE_PATH);
    background.setTexture(&backgroundTexture);
    background.setTextureRect(sf::IntRect(background.getPosition().x, background.getPosition().y, background.getSize().x, background.getSize().y));

    sf::Text winText;

    // ��������� ���� ����
    std::ofstream logFile;
    logFile.open("log.txt");

    // ������� ������ ����
    logFile.clear();

    // ������� ������ LevelGenerator
    LevelGenerator levelGenerator(MIRRORS_COUNT, TARGETS_COUNT, WINDOW_WIDTH, WINDOW_HEIGHT, SIZE);

    // ���������� �������
    logFile << "Generating level..." << std::endl;
    levelGenerator.generateLevel(SIZE);
    logFile << "Succesful" << std::endl;

    // �������� ������ ������
    logFile << "Getting level data..." << std::endl;
    std::vector mirrors = levelGenerator.getMirrors();
    std::vector targets = levelGenerator.getTargets();
    std::vector blocks = levelGenerator.getBlocks();
    sf::Vector2f gunPosition = levelGenerator.getGunPosition();
    logFile << "Succesful" << std::endl;

    // ������� �������� �����
    LaserGun gun(gunPosition.x, gunPosition.y, SIZE, 0.5, 0);

    logFile << "Loading textures..." << std::endl;
    // ��������� ��������
    sf::Texture mirrorTexture = loadTexture(MIRROR_TEXTURE_PATH);
    sf::Texture targetTexture = loadTexture(TARGET_TEXTURE_PATH);
    sf::Texture gunTexture = loadTexture(GUN_TEXTURE_PATH);
    logFile << "Succesful" << std::endl;

    // ������������� �������� ��� ��������
    for (auto& mirror : mirrors) {
        mirror.setTexture(mirrorTexture, MIRROR_TEXTURE_PATH.string());
    }
    for (auto& target : targets) {
        target.setTexture(targetTexture, TARGET_TEXTURE_PATH.string());
    }
    gun.setTexture(gunTexture, GUN_TEXTURE_PATH.string());

    // ������� ���� ����
    while (window.isOpen()) {

        sf::Event event; {
            while (window.pollEvent(event)) {

                // ��������� �������
                switch (event.type) {

                case sf::Event::Closed: {
                    window.close();
                    break;
                }

                case sf::Event::MouseButtonPressed: {

                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int mouseX = sf::Mouse::getPosition(window).x;
                        int mouseY = sf::Mouse::getPosition(window).y;

                        std::cout << mouseX << ' ' << mouseY << std::endl;

                        // ���������, ��������� �� ������ ��� �������� � ������ �����
                        for (auto& mirror : mirrors) {
                            if (mirror.isUnderCursor(mouseX, mouseY)) {
                                mirror.setSelection();
                                std::cout << "Mirror selected" << std::endl;
                                logFile << "Mirror selected" << std::endl;
                                break;
                            }
                            else {
                                mirror.clearSelection();
                            }
                        }

                        // ���������, ��������� �� ������ ��� ������ � ������ �����
                        if (gun.isUnderCursor(mouseX, mouseY)) {
                            gun.setSelection();
                            std::cout << "Gun selected" << std::endl;
                            logFile << "Gun selected" << std::endl;
                        }
                        else {
                            gun.clearSelection();
                        }
                        break;
                    }

                case sf::Event::KeyPressed: {

                    if (event.key.code == sf::Keyboard::Space) {
                        if (!gun.isActive()) {
                            gun.setVelocity((GameMath::getDirectionFromAngle(gun.getRotationAngle())));
                            gun.setActive(true);
                        }
                        std::cout << "LaserGun activated: " << gun.isActive() << std::endl;
                        logFile << "LaserGun activated: " << gun.isActive() << std::endl;
                    }
                    if (event.key.code == sf::Keyboard::R) {
                        gun.reset();
                        std::cout << "LaserGun reseted" << std::endl;
                        logFile << "LaserGun reseted" << std::endl;
                        gun.setActive(false);
                        std::cout << "LaserGun activated: " << gun.isActive() << std::endl;
                        logFile << "LaserGun activated: " << gun.isActive() << std::endl;
                        std::cout << "Velocity: " << gun.getLaserVelocity().x << " " << gun.getLaserVelocity().y << std::endl;
                        logFile << "Velocity: " << gun.getLaserVelocity().x << " " << gun.getLaserVelocity().y << std::endl;
                    }
                    if (event.key.code == sf::Keyboard::G) {

                        gun.reset();
                        mirrors.clear();
                        blocks.clear();
                        targets.clear();

                        levelGenerator.generateLevel(SIZE);

                        gun.setPosition(levelGenerator.getGunPosition().x, levelGenerator.getGunPosition().y);
                        mirrors = levelGenerator.getMirrors();
                        targets = levelGenerator.getTargets();
                        blocks = levelGenerator.getBlocks();

                        for (auto& mirror : mirrors) {
                            mirror.setTexture(mirrorTexture, MIRROR_TEXTURE_PATH.string());
                        }
                        for (auto& target : targets) {
                            target.setTexture(targetTexture, TARGET_TEXTURE_PATH.string());
                        }
                        gun.setTexture(gunTexture, GUN_TEXTURE_PATH.string());

                    }

                    // ��������� �������� ���������� �������
                    for (auto& mirror : mirrors) {
                        if (mirror.isSelected()) {
                            if (event.key.code == sf::Keyboard::Right) {
                                mirror.rotateRight();
                            }
                            else if (event.key.code == sf::Keyboard::Left) {
                                mirror.rotateLeft();
                            }
                            std::cout << "Mirror rotation angle: " << mirror.getRotationAngle() << std::endl;
                            logFile << "Mirror rotation angle: " << mirror.getRotationAngle() << std::endl;
                            break;
                        }
                    }

                    if (gun.isSelected()) {
                        if (event.key.code == sf::Keyboard::Right) {
                            gun.rotateRight();
                        }
                        else if (event.key.code == sf::Keyboard::Left) {
                            gun.rotateLeft();
                        }
                        std::cout << "Gun rotation angle: " << gun.getRotationAngle() << std::endl;
                        logFile << "Gun rotation angle: " << gun.getRotationAngle() << std::endl;
                    }

                    break;

                }

                }

                }
            }

            // ��������� ������������ ������
            for (auto& mirror : mirrors) {
                if (GameMath::checkLaserCollision(gun.getLaserGlobalBounds(), mirror.getGlobalBounds())) {
                    gun.setVelocity(gun.getReflectedVelocity(mirror.getDirection()));
                }
            }
            for (auto& target : targets) {
                if (GameMath::checkLaserCollision(gun.getLaserGlobalBounds(), target.getGlobalBounds())) {
                    target.destroy();
                }
            }
            for (auto& block : blocks) {
                if (GameMath::checkLaserCollision(gun.getLaserGlobalBounds(), block.getGlobalBounds())) {
                    gun.setVelocity(sf::Vector2f(0, 0));
                }
            }

            // ��������� ��������� �������� ������ �������� �����
            gun.update();
            for (auto& mirror : mirrors) {
                mirror.update();
            }
        }

        // ������� ����
        window.clear();

        // ������ ���
        window.draw(background);

        // ������ �������

        for (auto& mirror : mirrors) {
            mirror.draw(window);
            if (GameMath::checkLaserCollision(gun.getLaserGlobalBounds(), mirror.getGlobalBounds())) {
            }
            else {
                gun.drawLaser(window, 70);
            }
        }

        for (auto& target : targets) {
            target.draw(window);
        }

        for (auto& block : blocks) {
            block.showCollider();
            block.draw(window);
        }
        gun.draw(window);

        // ���������� ���������� ����
        window.display();

        logFile.close();
    }

    return 0;
}