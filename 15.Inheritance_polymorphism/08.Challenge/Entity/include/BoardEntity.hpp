#pragma once

#include "Board.hpp"
#include "Entity.hpp"

class BoardEntity : public Entity
{
public:
  BoardEntity(const Board &board);

  void update(float deltaTime) override;
  void draw(sf::RenderWindow &window) const override;

  void updateFromBoard(const Board &board);

private:
  std::vector<std::vector<sf::RectangleShape>> m_grid;
};