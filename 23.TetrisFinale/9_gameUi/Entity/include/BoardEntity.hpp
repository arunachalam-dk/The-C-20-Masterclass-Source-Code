#pragma once
#include "Entity.hpp"
#include "Board.hpp"

class BoardEntity : public Entity {
public:
  BoardEntity(const Board& board);

  void update(float deltaTime) override;
  void draw(sf::RenderWindow& window) const override;

  void updateFromBoard(const Board& board);

private:
  std::vector<std::vector<sf::RectangleShape>> m_grid;
};