#pragma once
#include <array>
#include <vector>

class Tetromino
{
public:
  enum class Type { I, O, T, S, Z, J, L };

  explicit Tetromino(Type type);
  void move(int dx, int dy);
  Tetromino getMovedPosition(int dx, int dy) const;
  const std::vector<std::array<int, 2>> &getBlocks() const { return blocks; }
  Type getType() const { return type; }

private:
  Type type;
  std::vector<std::array<int, 2>> blocks;
  int x, y;
};