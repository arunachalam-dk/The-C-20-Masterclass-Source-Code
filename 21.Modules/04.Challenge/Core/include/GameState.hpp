#pragma once
#include "Board.hpp"
#include "Tetromino.hpp"

class GameState {
public:
  GameState();
  void update(float deltaTime);
  void moveTetromino(int dx);
  void rotateTetromino();
  void hardDrop();
  void softDrop();

  const Board& getBoard() const { return board; }
  const Tetromino& getCurrentTetromino() const { return currentTetromino; }
  const Tetromino& getNextTetromino() const { return nextTetromino; }

private:
  Board board;
  Tetromino currentTetromino;
  Tetromino nextTetromino;
  float fallTimer;
  float softDropTimer;

  void spawnNewTetromino();
  void lockTetromino();
};