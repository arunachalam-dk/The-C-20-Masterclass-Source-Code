#pragma once
#include "Tetromino.hpp"
#include <vector>

class Board {
public:
  static constexpr int WIDTH = 10;
  static constexpr int HEIGHT = 20;

  Board();
  [[nodiscard]] bool isCollision(const Tetromino& tetromino) const noexcept;
  void placeTetromino(const Tetromino& tetromino);
  int clearLines();
  [[nodiscard]] bool isGameOver() const;

  [[nodiscard]] const std::vector<std::vector<int>>& getGrid() const { return grid; }

private:
  [[nodiscard]] bool hasNonEmptyCells(const Tetromino::BoundingBox& bb) const noexcept;
  [[nodiscard]] bool detailedCollisionCheck(const Tetromino& tetromino) const noexcept;

  std::vector<std::vector<int>> grid;
};