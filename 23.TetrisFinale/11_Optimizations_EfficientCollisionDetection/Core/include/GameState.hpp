#pragma once
#include "Board.hpp"
#include "Tetromino.hpp"
#include "ScoreManager.hpp"

class GameState {
public:
  GameState();
  void update(float deltaTime);
  void moveTetromino(int dx);
  void rotateTetromino();
  void hardDrop();
  void softDrop();
  bool isGameOver() const { return gameOver; }

  const Board& getBoard() const { return board; }
  const Tetromino& getCurrentTetromino() const { return currentTetromino; }
  const Tetromino& getNextTetromino() const { return nextTetromino; }
  const ScoreManager& getScoreManager() const { return scoreManager; }

private:
  Board board;
  Tetromino currentTetromino;
  Tetromino nextTetromino;
  ScoreManager scoreManager;
  float fallTimer;
  float softDropTimer;
  bool gameOver;

  void spawnNewTetromino();
  void lockTetromino();
};