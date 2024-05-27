// GameMath.h
#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include "Mirror.h"
#include "Target.h"

class GameMath {
public:
    // ��������� ���� �� �������
    static float getAngleFromVector(const sf::Vector2f& vector);

    // ��������� ������� ����������� �� ����
    static sf::Vector2f getDirectionFromAngle(float angle);

    // ���������� ���������� ����� ����� �������
    static float getDistance(const sf::Vector2f& point1, const sf::Vector2f& point2);

    // ������������ �������
    static sf::Vector2f normalize(const sf::Vector2f& vector);

    static int generateRandomAngle();

    // ������� �������� ������������ ������
    static bool checkLaserCollision(const sf::FloatRect& laser, const sf::FloatRect& rect2);

    // ������� ��� �������� ���������� ������ ������� ������
    static bool checkOverlap(const sf::FloatRect& rect1, const std::vector<sf::FloatRect>& rects);

    // ������� ��� �������� ������������ ����� � ���������
    static bool checkCollisionWithObjects(sf::Vector2i point, const std::vector<sf::FloatRect>& rects);

    // ��������� ����� � ��������� (int a, int b)
    static int generateRandomInt(int a, int b);

    static bool generateRandomBool();
    // ������� ��� ��������� ��������� ��������� � �������� ����
    static sf::Vector2f generateRandomPosition(int width, int height, const std::vector<sf::FloatRect>& occupiedRects, sf::Vector2f rectSize);

    // ������� ������ ������� ��� �������
    static sf::Vector2f findMirrorPosition(sf::Vector2f laserPos, sf::Vector2f targetPos, sf::Vector2f SIZE);

    // ������� ���������� ���� �������� ��� �������
    static float calculateMirrorAngle(sf::Vector2f laserPos, sf::Vector2f targetPos, sf::Vector2f mirrorPos);

    // ������� �������� ������ ��������� ����� ����� �������
    static bool checkLineOfSight(sf::Vector2f point1, sf::Vector2f point2, const std::vector<Mirror>& mirrors, sf::Vector2f SIZE);

    static sf::Vector2f findOptionalMirrorPosition(sf::Vector2f laserPos, sf::Vector2f targetPos, const std::vector<Mirror>& mirrors, sf::Vector2f SIZE);
};