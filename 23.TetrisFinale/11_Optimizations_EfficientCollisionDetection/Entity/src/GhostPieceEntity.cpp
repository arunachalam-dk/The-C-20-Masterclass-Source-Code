#include "GhostPieceEntity.hpp"

namespace {
const float BLOCK_SIZE = 30.0f;
const sf::Color GHOST_COLOR(128, 128, 128, 128);// Semi-transparent grey
}// namespace

GhostPieceEntity::GhostPieceEntity(const Tetromino &tetromino, const Board &board) { updatePosition(tetromino, board); }

void GhostPieceEntity::update(float deltaTime)
{
  // No update logic needed for now
}

void GhostPieceEntity::draw(sf::RenderWindow &window) const
{
  for (const auto &block : m_blocks) { window.draw(block); }
}

void GhostPieceEntity::updatePosition(const Tetromino& tetromino, const Board& board) {
  m_blocks.clear();

  Tetromino ghostTetromino = tetromino;
  while (!board.isCollision(ghostTetromino)) {
    ghostTetromino.move(0, 1);
  }
  ghostTetromino.move(0, -1);

  for (const auto& block : ghostTetromino.getBlocks()) {
    sf::RectangleShape shape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    shape.setPosition(block[0] * BLOCK_SIZE, block[1] * BLOCK_SIZE);
    shape.setFillColor(sf::Color(128, 128, 128, 128));  // Semi-transparent grey
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1.0f);
    m_blocks.push_back(shape);
  }
}
