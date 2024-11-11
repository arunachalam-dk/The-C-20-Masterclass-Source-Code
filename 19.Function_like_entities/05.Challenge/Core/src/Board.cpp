#include "Board.hpp"
#include "Tetromino.hpp"

Board::Board() : grid(HEIGHT, std::vector<int>(WIDTH, 0)) {}
bool Board::isCollision(const Tetromino &tetromino) const
{
  for (const auto& block : tetromino.getBlocks()) {
    int x = block[0];
    int y = block[1];
    if (x < 0 || x >= WIDTH || y >= HEIGHT) {
      return true;
    }
    if (y >= 0 && grid[y][x] != 0) {
      return true;
    }
  }
  return false;
}

void Board::placeTetromino(const Tetromino& tetromino) {
  for (const auto& block : tetromino.getBlocks()) {
    int x = block[0];
    int y = block[1];
    if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
      grid[y][x] = 0 + 1;
    }
  }
}