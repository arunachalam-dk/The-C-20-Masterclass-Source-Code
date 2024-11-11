#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "TetrominoEntity.hpp"
#include "BoardEntity.hpp"
#include "Renderer.hpp"
#include "Camera.hpp"

class Game {
public:
  Game();
  void run();

private:
  void processEvents();
  void update(float deltaTime);
  void render();

  void initializeGame();
  void handleKeyPress(sf::Keyboard::Key key);
  void updateEntities();
  void resetGame();

  sf::RenderWindow m_window;
  Renderer m_renderer;
  Camera m_camera;
  GameState m_gameState;

  TetrominoEntity m_currentTetrominoEntity;
  BoardEntity m_boardEntity;

  sf::Clock m_clock;
  float m_deltaTime;
};