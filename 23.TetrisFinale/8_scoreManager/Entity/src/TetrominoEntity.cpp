#include "TetrominoEntity.hpp"

namespace {
const float BLOCK_SIZE = 30.0f;
const std::array<sf::Color, 7> TETROMINO_COLORS = {
  sf::Color::Cyan,// I
  sf::Color::Yellow,// O
  sf::Color(128, 0, 128),// T (Purple)
  sf::Color::Green,// S
  sf::Color::Red,// Z
  sf::Color::Blue,// J
  sf::Color(255, 165, 0)// L (Orange)
};
}// namespace

TetrominoEntity::TetrominoEntity(const Tetromino &tetromino) { updateFromTetromino(tetromino); }

void TetrominoEntity::update(float deltaTime)
{
  // No update logic needed for now
}

void TetrominoEntity::draw(sf::RenderWindow &window) const
{
  for (const auto &block : m_blocks) { window.draw(block); }
}

void TetrominoEntity::updateFromTetromino(const Tetromino& tetromino) {
  m_blocks.clear();
  m_color = TETROMINO_COLORS[static_cast<int>(tetromino.getType())];

  for (const auto& block : tetromino.getBlocks()) {
    sf::RectangleShape shape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    shape.setPosition(block[0] * BLOCK_SIZE, block[1] * BLOCK_SIZE);
    shape.setFillColor(m_color);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1.0f);
    m_blocks.push_back(shape);
  }
}
