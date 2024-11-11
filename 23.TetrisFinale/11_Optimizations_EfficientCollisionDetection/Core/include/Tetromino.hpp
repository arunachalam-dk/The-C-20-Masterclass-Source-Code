#pragma once
#include <array>
#include <vector>
#include <bits/ranges_algo.h>

class Tetromino
{
public:
  enum class Type { I, O, T, S, Z, J, L };

  explicit Tetromino(Type type);
  void rotate(bool clockwise);
  void move(int dx, int dy);
  Tetromino getMovedPosition(int dx, int dy) const;
  const std::vector<std::array<int, 2>> &getBlocks() const { return blocks; }
  Type getType() const { return type; }

  struct BoundingBox {
    int left, right, top, bottom;
  };

  [[nodiscard]] BoundingBox getBoundingBox() const noexcept;

private:
  Type type;
  std::vector<std::array<int, 2>> blocks;
  int x, y;
};
