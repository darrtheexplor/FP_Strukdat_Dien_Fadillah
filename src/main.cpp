#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>

// KECEPATAN
const float SPEED_MULTIPLIER = 4.0f; 

// QUADTREE STRUCT
struct QuadTree {
    sf::FloatRect boundary;
    int capacity;
    std::vector<int> points;
    bool divided = false;

    QuadTree *NE = nullptr, *NW = nullptr, *SE = nullptr, *SW = nullptr;

    QuadTree(sf::FloatRect area, int cap) : boundary(area), capacity(cap) {}

    bool insert(int index, const sf::Vector2f &pos) {
        if (!boundary.contains(pos))
            return false;

        if (points.size() < capacity) {
            points.push_back(index);
            return true;
        }

        if (!divided)
            subdivide();

        if (NE->insert(index, pos)) return true;
        if (NW->insert(index, pos)) return true;
        if (SE->insert(index, pos)) return true;
        if (SW->insert(index, pos)) return true;

        return false;
    }

    void subdivide() {
        float x = boundary.left;
        float y = boundary.top;
        float w = boundary.width / 2.f;
        float h = boundary.height / 2.f;

        NE = new QuadTree({ x + w, y,     w, h }, capacity);
        NW = new QuadTree({ x,     y,     w, h }, capacity);
        SE = new QuadTree({ x + w, y + h, w, h }, capacity);
        SW = new QuadTree({ x,     y + h, w, h }, capacity);

        divided = true;
    }

    void query(sf::FloatRect range, std::vector<int> &found) {
        if (!boundary.intersects(range))
            return;

        for (int idx : points)
            found.push_back(idx);

        if (divided) {
            NE->query(range, found);
            NW->query(range, found);
            SE->query(range, found);
            SW->query(range, found);
        }
    }
};

// BALL STRUCT
struct Ball {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float radius;

    Ball(float x, float y, float r, sf::Vector2f vel, sf::Color color)
        : velocity(vel), radius(r)
    {
        velocity *= SPEED_MULTIPLIER;   

        shape.setRadius(r);
        shape.setFillColor(color);
        shape.setOrigin(r, r);
        shape.setPosition(x, y);
    }
};

// COLLISION FUNCTION
void checkCollision(Ball &A, Ball &B) {
    sf::Vector2f diff = B.shape.getPosition() - A.shape.getPosition();
    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    float minDist = A.radius + B.radius;

    if (dist < minDist) {
        if (dist == 0) dist = 0.01f;

        sf::Vector2f normal = diff / dist;
        float overlap = minDist - dist;

        A.shape.move(-normal * (overlap / 2.f));
        B.shape.move(normal * (overlap / 2.f));

        sf::Vector2f vA = A.velocity;
        sf::Vector2f vB = B.velocity;

        float a1 = vA.x * normal.x + vA.y * normal.y;
        float a2 = vB.x * normal.x + vB.y * normal.y;
        float p = (2.f * (a1 - a2)) / 2.f;

        A.velocity = vA - p * normal;
        B.velocity = vB + p * normal;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Brute Force + QuadTree Demo");
    window.setFramerateLimit(60);

    const int JUMLAH_BOLA = 10;
    bool useQuadTree = true;

    std::vector<Ball> balls;

    for (int i = 0; i < JUMLAH_BOLA; i++) {
        float radius = 20;
        float x = radius + rand() % (800 - (int)radius * 2);
        float y = radius + rand() % (600 - (int)radius * 2);

        sf::Vector2f velocity(rand() % 200 - 100, rand() % 200 - 100);

        balls.emplace_back(x, y, radius, velocity, sf::Color::White);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = 1.f / 60.f;

        // Update posisi bola
        for (auto &b : balls) {
            sf::Vector2f pos = b.shape.getPosition();
            pos += b.velocity * dt;

            if (pos.x - b.radius < 0) { pos.x = b.radius; b.velocity.x = -b.velocity.x; }
            if (pos.x + b.radius > 800) { pos.x = 800 - b.radius; b.velocity.x = -b.velocity.x; }
            if (pos.y - b.radius < 0) { pos.y = b.radius; b.velocity.y = -b.velocity.y; }
            if (pos.y + b.radius > 600) { pos.y = 600 - b.radius; b.velocity.y = -b.velocity.y; }

            b.shape.setPosition(pos);
        }

        // BRUTE FORCE
        if (!useQuadTree) {
            for (size_t i = 0; i < balls.size(); i++)
                for (size_t j = i + 1; j < balls.size(); j++)
                    checkCollision(balls[i], balls[j]);
        }

        // QUADTREE
        else {
            QuadTree qt({0, 0, 800, 600}, 4);

            for (int i = 0; i < balls.size(); i++)
                qt.insert(i, balls[i].shape.getPosition());

            for (int i = 0; i < balls.size(); i++) {
                sf::Vector2f pos = balls[i].shape.getPosition();
                float r = balls[i].radius * 2;
                sf::FloatRect range(pos.x - r, pos.y - r, r * 2, r * 2);

                std::vector<int> found;
                qt.query(range, found);

                for (int j : found)
                    if (i != j)
                        checkCollision(balls[i], balls[j]);
            }
        }

        window.clear();
        for (auto &b : balls)
            window.draw(b.shape);
        window.display();
    }

    return 0;
}
