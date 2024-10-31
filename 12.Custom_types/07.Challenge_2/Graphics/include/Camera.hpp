#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
public:
  Camera(float width, float height);

  const sf::View &getView() const;

private:
  sf::View m_view;
};