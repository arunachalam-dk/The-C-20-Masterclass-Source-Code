#pragma once
#include <BoardEntity.hpp>
#include <GameState.hpp>
#include <Renderer.hpp>
#include <SFML/Graphics.hpp>

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

  sf::RenderWindow m_window;

  Renderer m_renderer;
  Camera m_camera;
  GameState m_gameState;

  BoardEntity m_boardEntity;
};
