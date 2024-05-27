// GameMath.h
#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include "Mirror.h"
#include "Target.h"

class GameMath {
public:
    // Получение угла из вектора
    static float getAngleFromVector(const sf::Vector2f& vector);

    // Получение вектора направления из угла
    static sf::Vector2f getDirectionFromAngle(float angle);

    // Вычисление расстояния между двумя точками
    static float getDistance(const sf::Vector2f& point1, const sf::Vector2f& point2);

    // Нормализация вектора
    static sf::Vector2f normalize(const sf::Vector2f& vector);

    static int generateRandomAngle();

    // Функция проверки столкновений лазера
    static bool checkLaserCollision(const sf::FloatRect& laser, const sf::FloatRect& rect2);

    // Функция для проверки перекрытия одного объекта другим
    static bool checkOverlap(const sf::FloatRect& rect1, const std::vector<sf::FloatRect>& rects);

    // Функция для проверки столкновения точки с объектами
    static bool checkCollisionWithObjects(sf::Vector2i point, const std::vector<sf::FloatRect>& rects);

    // Случайное число в диапозоне (int a, int b)
    static int generateRandomInt(int a, int b);

    static bool generateRandomBool();
    // Функция для генерации случайных координат в пределах окна
    static sf::Vector2f generateRandomPosition(int width, int height, const std::vector<sf::FloatRect>& occupiedRects, sf::Vector2f rectSize);

    // Функция поиска позиции для зеркала
    static sf::Vector2f findMirrorPosition(sf::Vector2f laserPos, sf::Vector2f targetPos, sf::Vector2f SIZE);

    // Функция вычисления угла поворота для зеркала
    static float calculateMirrorAngle(sf::Vector2f laserPos, sf::Vector2f targetPos, sf::Vector2f mirrorPos);

    // Функция проверки прямой видимости между двумя точками
    static bool checkLineOfSight(sf::Vector2f point1, sf::Vector2f point2, const std::vector<Mirror>& mirrors, sf::Vector2f SIZE);

    static sf::Vector2f findOptionalMirrorPosition(sf::Vector2f laserPos, sf::Vector2f targetPos, const std::vector<Mirror>& mirrors, sf::Vector2f SIZE);
};