#pragma once

#include <vector>

class Board
{
public:
  static const int WIDTH = 10;
  static const int HEIGHT = 20;
  Board();
  const std::vector<std::vector<int>> &getGrid() const { return grid; }

private:
  std::vector<std::vector<int>> grid;
};