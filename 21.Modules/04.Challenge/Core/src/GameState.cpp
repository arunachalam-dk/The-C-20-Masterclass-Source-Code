#include "GameState.hpp"
#include "RandomGenerator.hpp"

GameState::GameState()
  : fallTimer(0),currentTetromino(RandomGenerator().getNextType()),
    nextTetromino(RandomGenerator().getNextType())
{}

void GameState::update(float deltaTime) {

  fallTimer += deltaTime;
  softDropTimer += deltaTime;

  // Adjust this calculation to slow down the speed increase
  float fallSpeed = 0.5f;

  // Add a minimum fall speed to prevent the game from becoming too fast
  fallSpeed = std::max(fallSpeed, 0.1f);  // Ensures the game doesn't get faster than 0.1 seconds per fall

  float softDropSpeed = fallSpeed / 4.0f;  // Soft drop is still 4 times faster than normal fall

  if (softDropTimer >= softDropSpeed) {
    softDropTimer = 0;
    softDrop();
  } else if (fallTimer >= fallSpeed) {
    fallTimer = 0;
    if (board.isCollision(currentTetromino.getMovedPosition(0, 1))) {
      lockTetromino();
    } else {
      currentTetromino.move(0, 1);
    }
  }
}
void GameState::moveTetromino(int dx)
{
  Tetromino movedTetromino = currentTetromino;
  movedTetromino.move(dx, 0);
  if (!board.isCollision(movedTetromino)) { currentTetromino = movedTetromino; }
}

void GameState::rotateTetromino()
{
  Tetromino rotatedTetromino = currentTetromino;
  rotatedTetromino.rotate(true);
  if (!board.isCollision(rotatedTetromino)) { currentTetromino = rotatedTetromino; }
}

void GameState::hardDrop()
{
  while (!board.isCollision(currentTetromino)) { currentTetromino.move(0, 1); }
  currentTetromino.move(0, -1);
  lockTetromino();
}
void GameState::softDrop()
{
  softDropTimer = 0;  // Reset the soft drop timer
  if (board.isCollision(currentTetromino.getMovedPosition(0, 1))) {
    lockTetromino();
  } else {
    currentTetromino.move(0, 1);
  }
}

void GameState::spawnNewTetromino()
{
  currentTetromino = nextTetromino;
  nextTetromino = Tetromino(RandomGenerator().getNextType());
}

void GameState::lockTetromino()
{
  board.placeTetromino(currentTetromino);
  board.clearLines();
  spawnNewTetromino();
}