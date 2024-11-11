
#pragma once
#include <vector>
#include <array>

class Tetromino
{
public:
  Tetromino();
  const std::vector<std::array<int, 2>> &getBlocks() const { return blocks; }
private:
  std::vector<std::array<int, 2>> blocks;
};
