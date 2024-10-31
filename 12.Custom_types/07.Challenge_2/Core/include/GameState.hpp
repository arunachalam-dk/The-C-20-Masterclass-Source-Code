#pragma once
#include <Board.hpp>

class GameState
{
public:
  GameState();

  const Board &getBoard() const { return board; }

private:
  Board board;
};
