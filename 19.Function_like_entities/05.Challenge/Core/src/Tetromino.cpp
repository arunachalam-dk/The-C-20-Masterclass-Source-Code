
#include "Tetromino.hpp"

Tetromino::Tetromino(): x(4), y(0)
{
  blocks = { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } };// Render 'I'
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