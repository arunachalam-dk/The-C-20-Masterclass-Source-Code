#pragma once

#include <SFML/Graphics.hpp>

class Entity
{
public:
  Entity();
  virtual ~Entity() = default;

  virtual void update(float deltaTime) = 0;
  virtual void draw(sf::RenderWindow &window) const = 0;

  void setPosition(const sf::Vector2f &position);
  const sf::Vector2f &getPosition() const;

protected:
  sf::Vector2f m_position;
};