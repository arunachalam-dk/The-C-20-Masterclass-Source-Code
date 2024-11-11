#include "GameState.hpp"
#include "RandomGenerator.hpp"

GameState::GameState()
  : fallTimer(0),currentTetromino(RandomGenerator().getNextType()),
    nextTetromino(RandomGenerator().getNextType())
{}

void GameState::update(float deltaTime) {

  fallTimer += deltaTime;

  // Adjust fall speed here
  float fallSpeed = 0.1f;

  if (fallTimer >= fallSpeed) {
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