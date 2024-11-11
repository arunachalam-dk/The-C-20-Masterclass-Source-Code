# Tetris Development Guide: Implementing Collision Detection

In this guide, we'll walk through the process of implementing collision detection for the Tetromino entity in our Tetris game. This is a crucial step in creating a functional Tetris game, as it prevents Tetrominos from moving through walls or other blocks, and determines when a Tetromino should be locked in place.

## 1. Updating the Board Class

### Step 1: Modify Board.hpp

Open `Core/include/Board.hpp` and update it as follows:

```c++
#pragma once
#include <vector>

class Tetromino;
class Board
{
public:
  static const int WIDTH = 10;
  static const int HEIGHT = 20;
  Board();
  bool isCollision(const Tetromino &tetromino) const;
  void placeTetromino(const Tetromino &tetromino);

  const std::vector<std::vector<int>> &getGrid() const { return grid; }

private:
  std::vector<std::vector<int>> grid;
};
```

**Why?**
- We've added an `isCollision` method to check if a Tetromino collides with the board or other blocks.
- We've added a `placeTetromino` method to lock a Tetromino in place when it lands.
- We've forward-declared the `Tetromino` class to avoid circular dependencies.

### Step 2: Implement Board Methods

Update `Core/src/Board.cpp`:

```c++
#include "Board.hpp"
#include "Tetromino.hpp"

Board::Board() : grid(HEIGHT, std::vector<int>(WIDTH, 0)) {}

bool Board::isCollision(const Tetromino &tetromino) const
{
  for (const auto& block : tetromino.getBlocks()) {
    int x = block[0];
    int y = block[1];
    if (x < 0 || x >= WIDTH || y >= HEIGHT) {
      return true;
    }
    if (y >= 0 && grid[y][x] != 0) {
      return true;
    }
  }
  return false;
}

void Board::placeTetromino(const Tetromino& tetromino) {
  for (const auto& block : tetromino.getBlocks()) {
    int x = block[0];
    int y = block[1];
    if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH) {
      grid[y][x] = 1; // We're using 1 to represent a placed block
    }
  }
}
```

**Why?**
- `isCollision` checks if any block of the Tetromino is outside the board boundaries or overlaps with an existing block.
- `placeTetromino` adds the Tetromino's blocks to the board grid, effectively locking it in place.

## 2. Updating the Tetromino Class

### Step 1: Modify Tetromino.hpp

Update `Core/include/Tetromino.hpp`:

```c++
#pragma once
#include <vector>
#include <array>

class Tetromino
{
public:
  Tetromino();
  void move(int dx, int dy);
  Tetromino getMovedPosition(int dx, int dy) const;
  const std::vector<std::array<int, 2>> &getBlocks() const { return blocks; }
private:
  int x, y;
  std::vector<std::array<int, 2>> blocks;
};
```

**Why?**
- We've added a `getMovedPosition` method to simulate a move without actually moving the Tetromino.

### Step 2: Implement Tetromino Methods

Update `Core/src/Tetromino.cpp`:

```c++
#include "Tetromino.hpp"

Tetromino::Tetromino(): x(4), y(0)
{
  blocks = { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } }; // Render 'I'
}

void Tetromino::move(int dx, int dy)
{
  x += dx;
  y += dy;
  for (auto &block : blocks) {
    block[0] += dx;
    block[1] += dy;
  }
}

Tetromino Tetromino::getMovedPosition(int dx, int dy) const
{
  Tetromino movedTetromino = *this;
  movedTetromino.move(dx, dy);
  return movedTetromino;
}
```

**Why?**
- `getMovedPosition` creates a copy of the Tetromino and moves it, allowing us to check for collisions before actually moving the Tetromino.

## 3. Updating the GameState Class

### Step 1: Modify GameState.hpp

Update `Core/include/GameState.hpp`:

```c++
#pragma once
#include <Board.hpp>
#include <Tetromino.hpp>

class GameState
{
public:
  GameState();

  void update(float deltaTime);
  void moveTetromino(int dx);
  const Board &getBoard() const { return board; }
  const Tetromino& getCurrentTetromino() const { return currentTetromino; }

private:
  Board board;
  Tetromino currentTetromino;

  float fallTimer;

  void lockTetromino();
};
```

**Why?**
- We've added a private `lockTetromino` method to handle the process of locking a Tetromino in place.

### Step 2: Implement GameState Methods

Update `Core/src/GameState.cpp`:

```c++
#include "GameState.hpp"

GameState::GameState() : fallTimer(0.f) {}

void GameState::update(float deltaTime)
{
  fallTimer += deltaTime;
  if (fallTimer >= 1.f) { // 1.0f max speed to allow for a move
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
  Tetromino movedTetromino = currentTetromino.getMovedPosition(dx, 0);
  if (!board.isCollision(movedTetromino)) {
    currentTetromino = movedTetromino;
  }
}

void GameState::lockTetromino() 
{
  board.placeTetromino(currentTetromino);
  // Here you would typically spawn a new Tetromino
}
```

**Why?**
- In `update`, we now check for collisions before moving the Tetromino down. If there's a collision, we lock the Tetromino in place.
- `moveTetromino` now checks for collisions before applying horizontal movement.
- `lockTetromino` places the current Tetromino on the board. In a complete game, this is where you'd spawn a new Tetromino.

## Result

With these changes, we've implemented basic collision detection in our Tetris game. Here's a summary of what we've achieved:

1. We've added collision detection to prevent Tetrominos from moving through walls or other blocks.
2. We've implemented the logic to lock Tetrominos in place when they land on the bottom or on other blocks.
3. We've updated the movement logic to respect collisions, both for automatic downward movement and player-controlled horizontal movement.

These changes significantly enhance the gameplay by enforcing the basic rules of Tetris. Tetrominos will now stack properly and the game will behave more like a traditional Tetris game.
![EntityCollisionDetection.gif](docs/5-entity-collision-detecton.gif)
