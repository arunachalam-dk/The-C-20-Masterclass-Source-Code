#pragma once

#include <Board.hpp>
#include <Tetromino.hpp>

class GameState
{
public:
  GameState();

  const Board &getBoard() const { return board; }
  const Tetromino& getCurrentTetromino() const { return currentTetromino; }

private:
  Board board;
  Tetromino currentTetromino;
};
