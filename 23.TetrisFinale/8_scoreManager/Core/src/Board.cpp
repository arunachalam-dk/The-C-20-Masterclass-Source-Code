#include "Board.hpp"
#include <algorithm>

Board::Board() : grid(HEIGHT, std::vector<int>(WIDTH, 0)) {}

bool Board::isCollision(const Tetromino& tetromino) const {
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
      grid[y][x] = static_cast<int>(tetromino.getType()) + 1;
    }
  }
}

int Board::clearLines() {
  int linesCleared = 0;
  auto it = std::remove_if(grid.begin(), grid.end(),
      [&](const std::vector<int>& row) {
          return std::all_of(row.begin(), row.end(), [](int cell) { return cell != 0; });
      });

  linesCleared = std::distance(it, grid.end());
  grid.erase(it, grid.end());

  while (grid.size() < HEIGHT) {
    grid.insert(grid.begin(), std::vector<int>(WIDTH, 0));
  }

  return linesCleared;
}

bool Board::isGameOver() const {
  return std::any_of(grid[0].begin(), grid[0].end(), [](int cell) { return cell != 0; });
}