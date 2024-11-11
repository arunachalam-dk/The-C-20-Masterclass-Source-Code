#pragma once
#include "Entity.hpp"
#include "Tetromino.hpp"

class TetrominoEntity : public Entity {
public:
  explicit TetrominoEntity(const Tetromino& tetromino);

  void update(float deltaTime) override;
  void draw(sf::RenderWindow& window) const override;

  void updateFromTetromino(const Tetromino& tetromino);

private:
  std::vector<sf::RectangleShape> m_blocks;
  sf::Color m_color;
};