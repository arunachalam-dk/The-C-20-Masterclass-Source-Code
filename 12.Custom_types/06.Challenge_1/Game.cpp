
#include "Game.hpp"
Game::Game() : m_window(sf::VideoMode(800, 600), "Tetris") {}

void Game::run()
{
  while (m_window.isOpen()) {
    processEvents();// handle user input
  }
}
void Game::handleKeyPress(sf::Keyboard::Key key) {}
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

