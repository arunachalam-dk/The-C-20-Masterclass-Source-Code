#include "BoardEntity.hpp"
#include <array>

namespace {
const float BLOCK_SIZE = 30.0f;
const std::array<sf::Color, 8> BLOCK_COLORS = {
  sf::Color::Black,// Empty
  sf::Color::Cyan,// I
  sf::Color::Yellow,// O
  sf::Color(128, 0, 128),// T (Purple)
  sf::Color::Green,// S
  sf::Color::Red,// Z
  sf::Color::Blue,// J
  sf::Color(255, 165, 0)// L (Orange)
};
}// namespace

BoardEntity::BoardEntity(const Board &board)
  : m_grid(Board::HEIGHT,
      std::vector<sf::RectangleShape>(Board::WIDTH, sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE))))
{
  updateFromBoard(board);
}

void BoardEntity::update(float deltaTime)
{
  // No update logic needed for now
}

void BoardEntity::draw(sf::RenderWindow &window) const
{
  for (const auto &row : m_grid) {
    for (const auto &cell : row) { window.draw(cell); }
  }
}

void BoardEntity::updateFromBoard(const Board &board)
{
  const auto &grid = board.getGrid();
  for (int y = 0; y < Board::HEIGHT; ++y) {
    for (int x = 0; x < Board::WIDTH; ++x) {
      m_grid[y][x].setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
      m_grid[y][x].setFillColor(BLOCK_COLORS[grid[y][x]]);
      m_grid[y][x].setOutlineColor(sf::Color::White);
      m_grid[y][x].setOutlineThickness(1.0f);
    }
  }
}