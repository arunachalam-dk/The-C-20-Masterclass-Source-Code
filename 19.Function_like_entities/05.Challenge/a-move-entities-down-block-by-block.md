# Tetris Development Guide: Implementing Entity Movement

In this guide, we'll walk through the process of implementing movement for entities in our Tetris game. We'll focus on moving the Tetromino downwards automatically and updating the game state and visual representations accordingly.

## 1. Updating the Tetromino Class

### Step 1: Modify Tetromino.hpp

Open `Core/include/Tetromino.hpp` and update it as follows:

```c++
#pragma once
#include <vector>
#include <array>

class Tetromino
{
public:
  Tetromino();
  void move(int dx, int dy);
  const std::vector<std::array<int, 2>> &getBlocks() const { return blocks; }
private:
  int x, y;
  std::vector<std::array<int, 2>> blocks;
};
```

**Why?**
- We've added a `move` method to allow the Tetromino to change its position.
- We've introduced `x` and `y` member variables to keep track of the Tetromino's position on the board.

### Step 2: Implement Tetromino Movement

Update `Core/src/Tetromino.cpp`:

```c++
#include "Tetromino.hpp"

Tetromino::Tetromino(): x(4), y(0)
{
  blocks = { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 } };// Render 'I'
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
```

**Why?**
- We initialize the Tetromino at the top-center of the board (x=4, y=0).
- The `move` method updates both the overall position (x, y) and each block's position.
- This allows us to move the entire Tetromino as a unit.

## 2. Updating the Game State

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

  void update();
  const Board &getBoard() const { return board; }
  const Tetromino& getCurrentTetromino() const { return currentTetromino; }

private:
  Board board;
  Tetromino currentTetromino;
};
```

**Why?**
- We've added an `update` method to the GameState class.
- This method will be responsible for updating the game state each frame, including moving the Tetromino.

### Step 2: Implement GameState Update

Modify `Core/src/GameState.cpp`:

```c++
#include "GameState.hpp"

GameState::GameState() = default;

void GameState::update()
{
  currentTetromino.move(0, 1);
}
```

**Why?**
- The `update` method moves the current Tetromino down by one unit (dy = 1) each time it's called.
- This creates the effect of the Tetromino falling down the board.

## 3. Updating the Game Loop

### Step 1: Modify Game.hpp

Update `Game.hpp`:

```c++
#pragma once
#include <BoardEntity.hpp>
#include <GameState.hpp>
#include <Renderer.hpp>
#include <SFML/Graphics.hpp>
#include <TetrominoEntity.hpp>

class Game
{
public:
  Game();
  void run();

private:
  void processEvents();
  void handleKeyPress(sf::Keyboard::Key key);
  void render();
  void initializeGame();
  void update();
  void updateEntities();

  sf::RenderWindow m_window;

  Renderer m_renderer;
  Camera m_camera;
  GameState m_gameState;

  BoardEntity m_boardEntity;
  TetrominoEntity m_currentTetrominoEntity;
};
```

**Why?**
- We've added `update` and `updateEntities` methods to the Game class.
- These methods will be responsible for updating the game state and refreshing the visual entities respectively.

### Step 2: Implement Game Update Methods

Update `Game.cpp`:

```c++
#include "Game.hpp"

// ... (previous code remains the same)

void Game::run()
{
  while (m_window.isOpen()) {
    processEvents();
    update();
    render();
  }
}

// ... (other methods remain the same)

void Game::update()
{
  m_gameState.update();
  updateEntities();
}

void Game::updateEntities()
{
  m_currentTetrominoEntity.updateFromTetromino(m_gameState.getCurrentTetromino());
  m_boardEntity.updateFromBoard(m_gameState.getBoard());
}
```

**Why?**
- We've modified the main game loop to include an update step between processing events and rendering.
- The `update` method updates the game state and then refreshes the visual entities.
- `updateEntities` syncs the visual representations (TetrominoEntity and BoardEntity) with their logical counterparts in the game state.

## Result

With these changes, we've implemented basic downward movement for the Tetromino in our Tetris game. Here's a summary of what we've achieved:

1. We've added movement capability to the Tetromino class.
2. We've implemented an update method in the GameState to move the Tetromino down each frame.
3. We've modified the main game loop to include an update step, keeping the visual representations in sync with the game state.

