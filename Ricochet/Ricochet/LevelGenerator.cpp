#include "LevelGenerator.h"

LevelGenerator::LevelGenerator(int mirrorsCount, int targetsCount, int height, int width, sf::Vector2f size) :
    MIRRORS_COUNT(mirrorsCount), TARGETS_COUNT(targetsCount),
    mirrors(MIRRORS_COUNT), targets(TARGETS_COUNT),
    WINDOW_HEIGHT(height), WINDOW_WIDTH(width),
    SIZE(size) {}


// ������� ��� ��������, ����� �� ����� ������� ���� � ������� ������������ ������
bool LevelGenerator::canLaserReachTarget(sf::Vector2f laserPos, sf::Vector2f targetPos, sf::Vector2f SIZE) {
    // 1. ���������� ����������� �� ������ � ����
    sf::Vector2f direction = targetPos - laserPos;
    float angle = GameMath::getAngleFromVector(direction);

    // 2. ���������, ����� �� ����� ������ ����� � ���� (��� ���������)
    if (GameMath::checkLineOfSight(laserPos, targetPos, mirrors, SIZE)) {
        return true;
    }

    // 3. ���������, ����� �� ����� ������ ����� �������
    for (int i = 0; i < mirrors.size(); ++i) {
        // ���������, ��������� �� ������� �� ���������� ������ � ����
        if (GameMath::checkLaserCollision(sf::FloatRect(laserPos.x, laserPos.y, SIZE.x, SIZE.y), mirrors[i].getGlobalBounds())) {
            // ���������, ����� �� ����� ������� ���� ����� ��������� �� �������
            sf::Vector2f reflectedDirection = GameMath::getDirectionFromAngle(GameMath::getAngleFromVector(direction) + 2 * (mirrors[i].getRotationAngle() - GameMath::getAngleFromVector(direction)));
            sf::Vector2f reflectedPos = laserPos + reflectedDirection * SIZE.x;
            if (GameMath::checkLineOfSight(reflectedPos, targetPos, mirrors, SIZE)) {
                return true;
            }
        }
    }

    return false;
}

// ��������� �������
void LevelGenerator::generateLevel(sf::Vector2f SIZE) {
    std::cout << "Generating..." << std::endl;

    // ��������� ����� ��������� ������
    int randomIndex = GameMath::generateRandomInt(0, levelStructures.size() - 1);
    const std::vector<LevelObject>& level = levelStructures[randomIndex];

    // ��������� ������
    gunPosition = level[0].position;

    // ��������� ������ � �����
    mirrors.clear();
    targets.clear();
    blocks.clear();

    for (int i = 0; i < level.size(); i++) {
        if (level[i].type == 'T') {
            targets.push_back(Target(level[i].position.x, level[i].position.y, SIZE));
        }else if (level[i].type == 'M') {
            mirrors.push_back(Mirror(level[i].position.x, level[i].position.y, SIZE, level[i].angle));
        }else if (level[i].type == 'B') {
            blocks.push_back(GameObject(level[i].position.x, level[i].position.y, SIZE));
        }
    }

    std::cout << "Succesful." << std::endl;
}


// ������� ��� ������������ ������������� ������
void LevelGenerator::visualizeLevel(sf::RenderWindow& window) {
    window.clear();

    // ��������� ������
    sf::VertexArray laserLine(sf::Lines, 2);
    laserLine[0].position = gunPosition;
    laserLine[1].position = gunPosition + sf::Vector2f(GameMath::getDirectionFromAngle(GameMath::generateRandomAngle()).x * 200, GameMath::getDirectionFromAngle(GameMath::generateRandomAngle()).y * 200);
    laserLine[0].color = sf::Color::Red;
    laserLine[1].color = sf::Color::Red;
    window.draw(laserLine);

    // ��������� ������
    for (const auto& mirror : mirrors) {
        sf::RectangleShape mirrorShape(sf::Vector2f(70, 70));
        mirrorShape.setPosition(mirror.getPosition());
        mirrorShape.setRotation(mirror.getRotationAngle());
        mirrorShape.setFillColor(sf::Color::Blue);
        window.draw(mirrorShape);
    }

    // ��������� �����
    for (const auto& target : targets) {
        sf::RectangleShape targetShape(sf::Vector2f(70, 70));
        targetShape.setPosition(target.getPosition());
        targetShape.setFillColor(sf::Color::Green);
        window.draw(targetShape);
    }

    window.display();
}