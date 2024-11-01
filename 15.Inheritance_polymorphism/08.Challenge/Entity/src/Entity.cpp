#include "Entity.hpp"


Entity::Entity() : m_position(0.0f, 0.0f) {}

void Entity::setPosition(const sf::Vector2f &position) { m_position = position; }

const sf::Vector2f &Entity::getPosition() const { return m_position; }