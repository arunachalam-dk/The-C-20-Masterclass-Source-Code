#pragma once
#include "Board.hpp"
#include "Tetromino.hpp"

class GameState {
public:
  GameState();
  void update(float deltaTime);
  void moveTetromino(int dx);

  const Board& getBoard() const { return board; }
  const Tetromino& getCurrentTetromino() const { return currentTetromino; }
  const Tetromino& getNextTetromino() const { return nextTetromino; }

private:
  Board board;
  Tetromino currentTetromino;
  Tetromino nextTetromino;
  float fallTimer;

  void spawnNewTetromino();
  void lockTetromino();
};