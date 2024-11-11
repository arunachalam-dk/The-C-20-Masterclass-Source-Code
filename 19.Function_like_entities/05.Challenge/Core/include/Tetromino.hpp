
#pragma once
#include <vector>
#include <array>

class Tetromino
{
public:
  Tetromino();
  void move(int dx, int dy);
  Tetromino getMovedPosition(int dx, int dy) const;
  const std::vector<std::array<int, 2>> &getBlocks() const { return blocks; }
private:
  int x, y;
  std::vector<std::array<int, 2>> blocks;
};
