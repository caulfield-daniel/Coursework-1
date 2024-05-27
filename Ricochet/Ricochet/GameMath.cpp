// GameMath.cpp
#include "GameMath.h"

float GameMath::getAngleFromVector(const sf::Vector2f& vector) {
    return std::atan2(vector.y, vector.x) * 180 / 3.14159265f; // ������� � �������
}

sf::Vector2f GameMath::getDirectionFromAngle(float angle) {
    float angleRad = angle * 3.14159265f / 180; // ������� � �������
    return sf::Vector2f(std::cos(angleRad), std::sin(angleRad));
}

float GameMath::getDistance(const sf::Vector2f& point1, const sf::Vector2f& point2) {
    return std::sqrt(std::pow(point2.x - point1.x, 2) + std::pow(point2.y - point1.y, 2));
}

sf::Vector2f GameMath::normalize(const sf::Vector2f& vector) {
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0) {
        return sf::Vector2f(vector.x / length, vector.y / length);
    }
    return vector; // ���������� �������� ������, ���� ����� ����� 0
}

// ������� ��������� ���������� ���� ��������
int GameMath::generateRandomAngle() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 11); // 12 ��������� ����� (0, 30, 60, ..., 330)

        return distrib(gen) * 30; // ���������� ��������� ����, ������� 30
    }

// ������� �������� ������������ ������
bool GameMath::checkLaserCollision(const sf::FloatRect & laser, const sf::FloatRect & rect2) {
        // ��������� ����������� ���������������
        if (laser.intersects(rect2)) {
            return true; // ������� �����������
        }
        return false; // ������� �� �����������
    }

// ������� ��� �������� ���������� ������ ������� ������
bool GameMath::checkOverlap(const sf::FloatRect & rect1, const std::vector<sf::FloatRect>&rects) {
        float offset = 100; // ������ ��� ���������� �������

        for (const auto& rect2 : rects) {
            // ��������� ����������� � ������ �������
            if (rect1.intersects(sf::FloatRect(rect2.left - offset, rect2.top - offset, rect2.width + 2 * offset, rect2.height + 2 * offset))) {
                return true;
            }
        }
        return false;
    }

// ������� ��� �������� ������������ ����� � ���������
bool GameMath::checkCollisionWithObjects(sf::Vector2i point, const std::vector<sf::FloatRect>& rects) {
    for (const auto& rect : rects) {
        if (rect.contains(sf::Vector2f(point.x, point.y))) {
            return true;
        }
    }
    return false;
}

// ������� ��� ��������� ��������� ��������� � �������� ����
sf::Vector2f GameMath::generateRandomPosition(int width, int height, const std::vector<sf::FloatRect>&occupiedRects, sf::Vector2f rectSize) {
        std::random_device rd;
        std::mt19937 gen(rd());

        while (true) {
            std::uniform_int_distribution<> xDist(0, width - static_cast<int>(rectSize.x));
            std::uniform_int_distribution<> yDist(0, height - static_cast<int>(rectSize.y));
            int x = xDist(gen);
            int y = yDist(gen);

            sf::FloatRect newRect(x, y, rectSize.x, rectSize.y);
            if (!checkOverlap(newRect, occupiedRects)) {
                return sf::Vector2f(x, y);
            }
        }
    }

// ��������� ����� � ��������� (int a, int b)
int GameMath::generateRandomInt(int a, int b) {
        srand(time(NULL));
        if (a > 0) return a + rand() % (b - a);
        else return a + rand() % (abs(a) + b);
}
// ������� ��� ���������� ������� ������������� �������
sf::Vector2f GameMath::findMirrorPosition(sf::Vector2f laserPos, sf::Vector2f targetPos, sf::Vector2f SIZE) {
    // ������� �����, ������� ��������� �� �������� ������ ����� ����� ������� � �����
    sf::Vector2f mirrorPos = (laserPos + targetPos) / 2.0f;

    // ��������� ��������� ��������, ����� �������� �������� � ������� ��� �����
    mirrorPos.x += SIZE.x*2;
    mirrorPos.y += SIZE.y*2;

    return mirrorPos;
}

bool GameMath::generateRandomBool() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_int_distribution<> distribution(0, 1); // 0 ��� 1

    return distribution(generator);
}

float GameMath::calculateMirrorAngle(sf::Vector2f laserPos, sf::Vector2f targetPos, sf::Vector2f mirrorPos) {
    // ������� ���� ����� �������� �� ������ �� ������� � �������� �� ������� �� ����
    sf::Vector2f laserToMirror = mirrorPos - laserPos;
    sf::Vector2f mirrorToTarget = targetPos - mirrorPos;
    float angle1 = getAngleFromVector(laserToMirror);
    float angle2 = getAngleFromVector(mirrorToTarget);

    // ��������� ���� �������� ������� (���� ����� ����� ���������)
    float mirrorAngle = (angle1 + angle2) / 2.0f;

    return mirrorAngle;
}

// �������� ������ ��������� ����� ����� �������
bool GameMath::checkLineOfSight(sf::Vector2f point1, sf::Vector2f point2, const std::vector<Mirror>& mirrors, sf::Vector2f SIZE) {
    // ���������, ���������� �� ������ ����� ����� point1 � point2 ����� �� �������� � mirrors
    for (const auto& mirror : mirrors) {
        if (checkLaserCollision(sf::FloatRect(point1.x, point1.y, SIZE.x, SIZE.y), mirror.getGlobalBounds())) {
            return false; // ����������� �������, ������ ��������� ���
        }
    }
    return true; // ����������� �� �������, ������ ��������� ����
}

sf::Vector2f GameMath::findOptionalMirrorPosition(sf::Vector2f laserPos, sf::Vector2f targetPos, const std::vector<Mirror>& mirrors, sf::Vector2f SIZE) {
    // 1. ���������, ���� �� ������ ��������� ����� ������� � �����
    if (GameMath::checkLineOfSight(laserPos, targetPos, mirrors, SIZE)) {
        // 2. ������ ���� ���������
        float mirrorAngle = GameMath::calculateMirrorAngle(laserPos, targetPos, (laserPos + targetPos) / 2.0f);

        // 3. ������ ����� �� ������, ������� ������������ ����� ���� ���������
        //    ��������� ���� ���������
        sf::Vector2f direction = GameMath::getDirectionFromAngle(mirrorAngle);
        sf::Vector2f potentialMirrorPos1 = laserPos + direction * SIZE.x * 2.0f; // ����� � 2 ���� ������ ������ 
        sf::Vector2f potentialMirrorPos2 = targetPos - direction * SIZE.x * 2.0f; // ����� � 2 ���� ������ ���� 

        std::vector<sf::FloatRect> mirrorRects;
        for (auto& mirror : mirrors) {
            mirrorRects.push_back(mirror.getGlobalBounds());
        }
        // 4. ���������, �� ������������ �� ��� ����� � ������� ���������
        if (!GameMath::checkOverlap(sf::FloatRect(potentialMirrorPos1.x, potentialMirrorPos1.y, SIZE.x, SIZE.y), mirrorRects) &&
            !GameMath::checkOverlap(sf::FloatRect(potentialMirrorPos2.x, potentialMirrorPos2.y, SIZE.x, SIZE.y), mirrorRects)) {
            // ���� ����������� ���, �������� �����, ������� ����� � ��������
            if (GameMath::getDistance(potentialMirrorPos1, (laserPos + targetPos) / 2.0f) < GameMath::getDistance(potentialMirrorPos2, (laserPos + targetPos) / 2.0f)) {
                return potentialMirrorPos1;
            }
            else {
                return potentialMirrorPos2;
            }
        }
    }
    return sf::Vector2f(-1, -1); // �� �������
}