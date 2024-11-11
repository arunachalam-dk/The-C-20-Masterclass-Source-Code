#pragma once
#include <array>
#include <vector>
#include <bits/ranges_algo.h>

class Tetromino
{
public:
  enum class Type { I, O, T, S, Z, J, L };

  Tetromino() : type(Type::I) {} // Default constructor
  explicit Tetromino(Type type);
  void rotate(bool clockwise);
  void move(int dx, int dy);
  [[nodiscard]] Tetromino getMovedPosition(int dx, int dy) const;
  [[nodiscard]] const std::vector<std::array<int, 2>> &getBlocks() const { return blocks; }
  [[nodiscard]] Type getType() const { return type; }

  struct BoundingBox {
    int left, right, top, bottom;
  };

  [[nodiscard]] BoundingBox getBoundingBox() const noexcept;

private:
  Type type;
  std::vector<std::array<int, 2>> blocks;
  int x{}, y{};
};
