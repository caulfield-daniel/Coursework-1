#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.h"
#include "Mirror.h"
#include "LaserGun.h"
#include "Target.h"
#include "GameMath.h"
#include <vector>
#include <random>
#include <algorithm>

// LevelGenerator.h
class LevelGenerator {

private:

    const int WINDOW_HEIGHT;		// ������� ����
    const int WINDOW_WIDTH;

    const sf::Vector2f SIZE;

    const int MIRRORS_COUNT;		// ���������� ������
    const int TARGETS_COUNT;		// � ����� �� ������

    std::vector<Mirror> mirrors;	// ������ ������
    std::vector<Target> targets;	// ������ �����
    std::vector<GameObject> blocks;	// ������ ������

    sf::Vector2f gunPosition;       // ������� ���������

public:
    LevelGenerator(int mirrorsCount, int targetsCount, int height, int width, sf::Vector2f size);

    // ��������� ����������� ������
    void generateLevel(sf::Vector2f SIZE);

    // ������������ ������������� ������
    void visualizeLevel(sf::RenderWindow& window);

    // ��������� ������� ������
    std::vector<Mirror> getMirrors() const { return mirrors; }

    // ��������� ������� �����
    std::vector<Target> getTargets() const { return targets; }
    
    // ��������� ������� ������
    std::vector<GameObject> getBlocks() const { return blocks; }

    // ��������� ������� �����
    sf::Vector2f getGunPosition() const { return gunPosition; }

private:
    // ������� ��� ��������, ����� �� ����� ������� ���� � ������� ������������ ������
    bool canLaserReachTarget(sf::Vector2f laserPos, sf::Vector2f targetPos, sf::Vector2f SIZE);
};


// ��������� ��� ��������� �������� ������
struct LevelObject {
    sf::Vector2f position;
    int angle; // ��� Mirror
    char type; // ����������� ���� �������
};

// ��������� ������� (������ ������� �������� � ����)
const std::vector<std::vector<LevelObject>> levelStructures = {
    // ������� 1
    {
        { sf::Vector2f(300, 200), 0, 'L'}, // LaserGun
        { sf::Vector2f(660, 200), 120, 'M'}, // Mirror
        { sf::Vector2f(470, 470), 30, 'M'}, // Mirror
        { sf::Vector2f(550, 350), 0, 'T'}, // Target
        { sf::Vector2f(71, 464), 0, 'T'}, // Target
        { sf::Vector2f(400, 260), 0, 'B'},   // Block
        { sf::Vector2f(126, 166), 0, 'B'},   // Block
        { sf::Vector2f(169, 357), 0, 'B'}   // Block
    },
    // ������� 2
    {
        { sf::Vector2f(607, 82), 60, 'L'}, // LaserGun
        { sf::Vector2f(608, 514), 0, 'M'}, // Mirror
        { sf::Vector2f(490, 220), 30, 'M'}, // Mirror
        { sf::Vector2f(465, 576), 120, 'M'}, // Mirror
        { sf::Vector2f(772, 100), 0, 'T'}, // Target
        { sf::Vector2f(219, 255), 0, 'T'}, // Target
        { sf::Vector2f(475, 40), 0, 'B'},   // Block
        { sf::Vector2f(475, 90), 0, 'B'},   // Block
        { sf::Vector2f(680, 70), 0, 'B'}   // Block
    },
    // ������� 3
    {
        { sf::Vector2f(70, 80), 0, 'L'}, // LaserGun
        { sf::Vector2f(720, 80), 180, 'M'}, // Mirror
        { sf::Vector2f(760, 180), 30, 'M'}, // Mirror
        { sf::Vector2f(771, 23), 0, 'T'}, // Target
        { sf::Vector2f(420, 565), 0, 'T'}, // Target
        { sf::Vector2f(0, 0), 0, 'B'},   // Block
        { sf::Vector2f(0, 0), 0, 'B'},   // Block
        { sf::Vector2f(0, 0), 0, 'B'}   // Block
    },
    // ������� 4
    {
        { sf::Vector2f(390, 255), 0, 'L'}, // LaserGun
        { sf::Vector2f(556, 247), 180, 'M'}, // Mirror
        { sf::Vector2f(385, 138), 90, 'M'}, // Mirror
        { sf::Vector2f(219, 247), 0, 'M'}, // Mirror
        { sf::Vector2f(397, 401), -90, 'M'}, // Mirror
        { sf::Vector2f(450, 23), 0, 'T'}, // Target
        { sf::Vector2f(420, 565), 0, 'T'}, // Target
        { sf::Vector2f(285, 19), 0, 'T'}, // Target
    },
    // ������� 5
    {
        { sf::Vector2f(67, 517), 0, 'L'}, // LaserGun
        { sf::Vector2f(556, 247), 180, 'M'}, // Mirror
        { sf::Vector2f(385, 138), 90, 'M'}, // Mirror
        { sf::Vector2f(219, 247), 0, 'M'}, // Mirror
        { sf::Vector2f(397, 401), -90, 'M'}, // Mirror
        { sf::Vector2f(204, 570), 0, 'T'}, // Target
        { sf::Vector2f(430, 565), 0, 'T'}, // Target
        { sf::Vector2f(285, 19), 0, 'T'}, // Target
        { sf::Vector2f(140, 490), 0, 'B'}, // Block
        { sf::Vector2f(140, 545), 0, 'B'}, // Block
    },
    
};