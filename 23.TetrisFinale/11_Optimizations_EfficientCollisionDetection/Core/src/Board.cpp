#include "Board.hpp"
#include <algorithm>
#include <ranges>

Board::Board() : grid(HEIGHT, std::vector<int>(WIDTH, 0)) {}

bool Board::isCollision(const Tetromino& tetromino) const noexcept{
  auto bb = tetromino.getBoundingBox();

  // Bounding box check
  if (bb.left < 0 || bb.right >= WIDTH || bb.bottom >= HEIGHT) {
    return true;
  }

  // If bounding box overlaps with non-empty cells, do a detailed check
  if (bb.top >= 0 && hasNonEmptyCells(bb)) {
    return detailedCollisionCheck(tetromino);
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

bool Board::hasNonEmptyCells(const Tetromino::BoundingBox &bb) const noexcept {
  return std::ranges::any_of(std::views::iota(std::max(0, bb.top), std::min(HEIGHT, bb.bottom + 1)),
      [this, &bb](int y) {
          return std::ranges::any_of(std::views::iota(bb.left, bb.right + 1),
              [this, y](int x) { return grid[y][x] != 0; });
      });
}

bool Board::detailedCollisionCheck(const Tetromino &tetromino) const noexcept  {
  return std::ranges::any_of(tetromino.getBlocks(), [this](const auto& block) {
      int x = block[0];
      int y = block[1];
      return y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH && grid[y][x] != 0;
  });
}