#include "GameState.hpp"


GameState::GameState() : fallTimer(0.f) {}
void GameState::update(float deltaTime)
{
  fallTimer += deltaTime;
  if (fallTimer >= 1.f) {// 1.0f max speed to allow for a move
    if (board.isCollision(currentTetromino.getMovedPosition(0, 1))) {
      lockTetromino();
    } else {
      currentTetromino.move(0, 1);
    }
    fallTimer = 0.f;
  }
}
void GameState::moveTetromino(int dx)
{
  Tetromino movedTetromino = currentTetromino;
  movedTetromino.move(dx, 0);
  if (!board.isCollision(movedTetromino)) { currentTetromino = movedTetromino; }
}

void GameState::lockTetromino() { board.placeTetromino(currentTetromino); }