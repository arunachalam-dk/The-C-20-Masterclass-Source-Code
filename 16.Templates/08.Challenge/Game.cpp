#include "Game.hpp"


Game::Game()
  : m_window(sf::VideoMode(800, 600), "TetrisSFML"), m_boardEntity(m_gameState.getBoard()), m_renderer(m_window),
    m_camera(800.f, 600.f), m_currentTetrominoEntity(m_gameState.getCurrentTetromino())
{
  initializeGame();
}


void Game::run()
{
  while (m_window.isOpen()) {
    processEvents();
    render();
  }
}
void Game::processEvents()
{
  sf::Event event;
  while (m_window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      m_window.close();
    } else if (event.type == sf::Event::KeyPressed) {
      handleKeyPress(event.key.code);
    }
  }
}
void Game::handleKeyPress(sf::Keyboard::Key key)
{
  // TODO - Handle key presses
}
void Game::render()
{
  m_renderer.beginDraw();

  m_boardEntity.draw(m_window);
  m_currentTetrominoEntity.draw(m_window);

  m_renderer.endDraw();
}
void Game::initializeGame()
{
  // Set up the window
  m_window.setFramerateLimit(60);

  // Initialize the camera
  m_renderer.setView(m_camera);

  // Set up the game board
  m_boardEntity.setPosition(sf::Vector2f(50, 50));

}