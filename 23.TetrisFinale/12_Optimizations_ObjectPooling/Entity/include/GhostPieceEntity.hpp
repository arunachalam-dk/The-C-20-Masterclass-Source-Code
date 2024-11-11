#pragma once
#include "Entity.hpp"
#include "Tetromino.hpp"
#include "Board.hpp"

class GhostPieceEntity : public Entity {
public:
  GhostPieceEntity(const Tetromino& tetromino, const Board& board);

  void update(float deltaTime) override;
  void draw(sf::RenderWindow& window) const override;

  void updatePosition(const Tetromino& tetromino, const Board& board);

private:
  std::vector<sf::RectangleShape> m_blocks;
};