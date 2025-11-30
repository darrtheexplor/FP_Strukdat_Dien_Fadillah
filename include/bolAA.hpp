#ifndef BOLAA_HPP
#define BOLAA_HPP

#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball(float x, float y, float radius, sf::Vector2f velocity, sf::Color color);

    void update(float dt, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    float getRadius() const;

    void setVelocity(sf::Vector2f vel);

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

#endif