#include "GameState.hpp"
#include "RandomGenerator.hpp"

GameState::GameState()
  : fallTimer(0), gameOver(false), tetrominoPool(20)
{
  currentTetromino = tetrominoPool.acquire(randomGenerator.getNextType());
  nextTetromino = tetrominoPool.acquire(randomGenerator.getNextType());
}

void GameState::update(float deltaTime) {
  if (gameOver) return;

  fallTimer += deltaTime;
  softDropTimer += deltaTime;

  // Adjust this calculation to slow down the speed increase
  float fallSpeed = 1.0f - (0.05f * scoreManager.getLevel());  // Changed from 0.1f to 0.05f

  // Add a minimum fall speed to prevent the game from becoming too fast
  fallSpeed = std::max(fallSpeed, 0.1f);  // Ensures the game doesn't get faster than 0.1 seconds per fall

  float softDropSpeed = fallSpeed / 4.0f;  // Soft drop is still 4 times faster than normal fall

  if (softDropTimer >= softDropSpeed) {
    softDropTimer = 0;
    softDrop();
  } else if (fallTimer >= fallSpeed) {
    fallTimer = 0;
    if (board.isCollision(currentTetromino->getMovedPosition(0, 1))) {
      lockTetromino();
    } else {
      currentTetromino->move(0, 1);
    }
  }
}
void GameState::moveTetromino(int dx) {
  if (gameOver) return;

  auto movedTetromino = tetrominoPool.acquire(*currentTetromino);
  movedTetromino->move(dx, 0);
  if (!board.isCollision(*movedTetromino)) {
    std::swap(currentTetromino, movedTetromino);
  }
  tetrominoPool.release(movedTetromino);
}

void GameState::rotateTetromino() {
  if (gameOver) return;

  auto rotatedTetromino = tetrominoPool.acquire(*currentTetromino);
  rotatedTetromino->rotate(true);
  if (!board.isCollision(*rotatedTetromino)) {
    std::swap(currentTetromino, rotatedTetromino);
  }
  tetrominoPool.release(rotatedTetromino);
}


void GameState::hardDrop()
{
  if (gameOver) return;

  while (!board.isCollision(*currentTetromino)) { currentTetromino->move(0, 1); }
  currentTetromino->move(0, -1);
  lockTetromino();
}
void GameState::softDrop()
{
  softDropTimer = 0;  // Reset the soft drop timer
  if (board.isCollision(currentTetromino->getMovedPosition(0, 1))) {
    lockTetromino();
  } else {
    currentTetromino->move(0, 1);
    scoreManager.addScore(1);  // Add a small score for soft dropping
  }
}

void GameState::spawnNewTetromino() {
  // Move the next Tetromino to current
  currentTetromino = std::move(nextTetromino);

  // Create a new next Tetromino
  nextTetromino = tetrominoPool.acquire(randomGenerator.getNextType());

  if (board.isCollision(*currentTetromino)) {
    gameOver = true;
  }
}

void GameState::lockTetromino() {
  board.placeTetromino(*currentTetromino);
  int linesCleared = board.clearLines();
  scoreManager.addScore(linesCleared);
  spawnNewTetromino();
}