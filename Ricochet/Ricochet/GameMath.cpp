// GameMath.cpp
#include "GameMath.h"

float GameMath::getAngleFromVector(const sf::Vector2f& vector) {
    return std::atan2(vector.y, vector.x) * 180 / 3.14159265f; // Перевод в градусы
}

sf::Vector2f GameMath::getDirectionFromAngle(float angle) {
    float angleRad = angle * 3.14159265f / 180; // Перевод в радианы
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
    return vector; // Возвращаем исходный вектор, если длина равна 0
}

// Функция генерация случайного угла поворота
int GameMath::generateRandomAngle() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 11); // 12 возможных углов (0, 30, 60, ..., 330)

        return distrib(gen) * 30; // Возвращаем случайный угол, кратный 30
    }

// Функция проверки столкновений лазера
bool GameMath::checkLaserCollision(const sf::FloatRect & laser, const sf::FloatRect & rect2) {
        // Проверяем пересечение прямоугольников
        if (laser.intersects(rect2)) {
            return true; // Объекты столкнулись
        }
        return false; // Объекты не столкнулись
    }

// Функция для проверки перекрытия одного объекта другим
bool GameMath::checkOverlap(const sf::FloatRect & rect1, const std::vector<sf::FloatRect>&rects) {
        float offset = 100; // Отступ для увеличения размера

        for (const auto& rect2 : rects) {
            // Проверяем пересечение с учетом отступа
            if (rect1.intersects(sf::FloatRect(rect2.left - offset, rect2.top - offset, rect2.width + 2 * offset, rect2.height + 2 * offset))) {
                return true;
            }
        }
        return false;
    }

// Функция для проверки столкновения точки с объектами
bool GameMath::checkCollisionWithObjects(sf::Vector2i point, const std::vector<sf::FloatRect>& rects) {
    for (const auto& rect : rects) {
        if (rect.contains(sf::Vector2f(point.x, point.y))) {
            return true;
        }
    }
    return false;
}

// Функция для генерации случайных координат в пределах окна
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

// Случайное число в диапозоне (int a, int b)
int GameMath::generateRandomInt(int a, int b) {
        srand(time(NULL));
        if (a > 0) return a + rand() % (b - a);
        else return a + rand() % (abs(a) + b);
}
// Функция для вычисления позиции генерируемого зеркала
sf::Vector2f GameMath::findMirrorPosition(sf::Vector2f laserPos, sf::Vector2f targetPos, sf::Vector2f SIZE) {
    // Находим точку, которая находится на середине прямой линии между лазером и целью
    sf::Vector2f mirrorPos = (laserPos + targetPos) / 2.0f;

    // Добавляем небольшое смещение, чтобы избежать коллизий с лазером или целью
    mirrorPos.x += SIZE.x*2;
    mirrorPos.y += SIZE.y*2;

    return mirrorPos;
}

bool GameMath::generateRandomBool() {
    static std::random_device rd;
    static std::mt19937 generator(rd());
    static std::uniform_int_distribution<> distribution(0, 1); // 0 или 1

    return distribution(generator);
}

float GameMath::calculateMirrorAngle(sf::Vector2f laserPos, sf::Vector2f targetPos, sf::Vector2f mirrorPos) {
    // Находим угол между вектором от лазера до зеркала и вектором от зеркала до цели
    sf::Vector2f laserToMirror = mirrorPos - laserPos;
    sf::Vector2f mirrorToTarget = targetPos - mirrorPos;
    float angle1 = getAngleFromVector(laserToMirror);
    float angle2 = getAngleFromVector(mirrorToTarget);

    // Вычисляем угол поворота зеркала (угол между этими векторами)
    float mirrorAngle = (angle1 + angle2) / 2.0f;

    return mirrorAngle;
}

// Проверка прямой видимости между двумя точками
bool GameMath::checkLineOfSight(sf::Vector2f point1, sf::Vector2f point2, const std::vector<Mirror>& mirrors, sf::Vector2f SIZE) {
    // Проверить, пересекает ли прямая линия между point1 и point2 любой из объектов в mirrors
    for (const auto& mirror : mirrors) {
        if (checkLaserCollision(sf::FloatRect(point1.x, point1.y, SIZE.x, SIZE.y), mirror.getGlobalBounds())) {
            return false; // Пересечение найдено, прямой видимости нет
        }
    }
    return true; // Пересечений не найдено, прямая видимость есть
}

sf::Vector2f GameMath::findOptionalMirrorPosition(sf::Vector2f laserPos, sf::Vector2f targetPos, const std::vector<Mirror>& mirrors, sf::Vector2f SIZE) {
    // 1. Проверяем, есть ли прямая видимость между лазером и целью
    if (GameMath::checkLineOfSight(laserPos, targetPos, mirrors, SIZE)) {
        // 2. Найдем угол отражения
        float mirrorAngle = GameMath::calculateMirrorAngle(laserPos, targetPos, (laserPos + targetPos) / 2.0f);

        // 3. Найдем точки на прямой, которые потенциально могут быть зеркалами
        //    используя угол отражения
        sf::Vector2f direction = GameMath::getDirectionFromAngle(mirrorAngle);
        sf::Vector2f potentialMirrorPos1 = laserPos + direction * SIZE.x * 2.0f; // Точка в 2 раза дальше лазера 
        sf::Vector2f potentialMirrorPos2 = targetPos - direction * SIZE.x * 2.0f; // Точка в 2 раза дальше цели 

        std::vector<sf::FloatRect> mirrorRects;
        for (auto& mirror : mirrors) {
            mirrorRects.push_back(mirror.getGlobalBounds());
        }
        // 4. Проверяем, не пересекаются ли эти точки с другими объектами
        if (!GameMath::checkOverlap(sf::FloatRect(potentialMirrorPos1.x, potentialMirrorPos1.y, SIZE.x, SIZE.y), mirrorRects) &&
            !GameMath::checkOverlap(sf::FloatRect(potentialMirrorPos2.x, potentialMirrorPos2.y, SIZE.x, SIZE.y), mirrorRects)) {
            // Если пересечений нет, выбираем точку, которая ближе к середине
            if (GameMath::getDistance(potentialMirrorPos1, (laserPos + targetPos) / 2.0f) < GameMath::getDistance(potentialMirrorPos2, (laserPos + targetPos) / 2.0f)) {
                return potentialMirrorPos1;
            }
            else {
                return potentialMirrorPos2;
            }
        }
    }
    return sf::Vector2f(-1, -1); // Не найдено
}