#pragma once

#include <Board.hpp>
#include <Tetromino.hpp>

class GameState
{
public:
  GameState();

  void update(float deltaTime);
  void moveTetromino(int dx);
  const Board &getBoard() const { return board; }
  const Tetromino& getCurrentTetromino() const { return currentTetromino; }

private:
  Board board;
  Tetromino currentTetromino;

  float fallTimer;

  void lockTetromino();
};
