#include "bolAA.hpp"

Ball::Ball(float x, float y, float radius, sf::Vector2f velocity, sf::Color color) {
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);
    shape.setFillColor(color);
    this->velocity = velocity;
}

void Ball::update(float dt, const sf::RenderWindow& window) {
    sf::Vector2f pos = shape.getPosition();
    pos += velocity * dt;

    float r = shape.getRadius();

    // Collision dengan bounds window
    if (pos.x - r < 0) { pos.x = r; velocity.x *= -1; }
    if (pos.x + r > window.getSize().x) { pos.x = window.getSize().x - r; velocity.x *= -1; }

    if (pos.y - r < 0) { pos.y = r; velocity.y *= -1; }
    if (pos.y + r > window.getSize().y) { pos.y = window.getSize().y - r; velocity.y *= -1; }

    shape.setPosition(pos);
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::Vector2f Ball::getPosition() const { return shape.getPosition(); }
sf::Vector2f Ball::getVelocity() const { return velocity; }
float Ball::getRadius() const { return shape.getRadius(); }

void Ball::setVelocity(sf::Vector2f vel) { velocity = vel; }
