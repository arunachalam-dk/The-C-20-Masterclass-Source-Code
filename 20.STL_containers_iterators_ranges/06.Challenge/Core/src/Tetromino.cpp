#include "Tetromino.hpp"
#include <array>

Tetromino::Tetromino(Type type) : type(type), x(4), y(0)
{
  switch (type) {
  case Type::I:
    blocks = { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } };
    break;
  case Type::O:
    blocks = { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 } };
    break;
  case Type::T:
    blocks = { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } };
    break;
  case Type::S:
    blocks = { { 1, 0 }, { 2, 0 }, { 0, 1 }, { 1, 1 } };
    break;
  case Type::Z:
    blocks = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 } };
    break;
  case Type::J:
    blocks = { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } };
    break;
  case Type::L:
    blocks = { { 2, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 } };
    break;
  }
}

void Tetromino::move(int dx, int dy)
{
  x += dx;
  y += dy;
  for (auto &block : blocks) {
    block[0] += dx;
    block[1] += dy;
  }
}
Tetromino Tetromino::getMovedPosition(int dx, int dy) const
{
  Tetromino movedTetromino = *this;
  movedTetromino.move(dx, dy);
  return movedTetromino;
}