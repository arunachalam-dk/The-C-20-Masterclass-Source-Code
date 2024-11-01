#pragma once
#include "Camera.hpp"
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class Renderer
{
public:
  Renderer(sf::RenderWindow &window);

  void beginDraw();
  void draw(const Entity &entity);
  void endDraw();

  void setView(const Camera &camera);

private:
  sf::RenderWindow &m_window;
};