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
  void update(float deltaTime);
  void updateEntities();

  sf::RenderWindow m_window;

  Renderer m_renderer;
  Camera m_camera;
  GameState m_gameState;

  BoardEntity m_boardEntity;
  TetrominoEntity m_currentTetrominoEntity;

  sf::Clock m_clock;
  float m_deltaTime;
};
