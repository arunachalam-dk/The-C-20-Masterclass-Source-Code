#pragma once
#include <RandomGenerator.hpp>

#include "Board.hpp"
#include "Tetromino.hpp"
#include "ScoreManager.hpp"
#include "ObjectPool.hpp"

class GameState {
public:
  GameState();
  void update(float deltaTime);
  void moveTetromino(int dx);
  void rotateTetromino();
  void hardDrop();
  void softDrop();
  [[nodiscard]] bool isGameOver() const noexcept { return gameOver; }

  [[nodiscard]] const Board& getBoard() const noexcept { return board; }
  [[nodiscard]] const Tetromino& getCurrentTetromino() const noexcept { return *currentTetromino; }
  [[nodiscard]] const Tetromino& getNextTetromino() const noexcept { return *nextTetromino; }
  [[nodiscard]] const ScoreManager& getScoreManager() const noexcept { return scoreManager; }

private:
  Board board;
  std::shared_ptr<Tetromino> currentTetromino;
  std::shared_ptr<Tetromino> nextTetromino;
  ObjectPool<Tetromino> tetrominoPool;

  ScoreManager scoreManager;
  RandomGenerator randomGenerator;
  float fallTimer;
  float softDropTimer{};
  bool gameOver;

  void spawnNewTetromino();
  void lockTetromino();
};