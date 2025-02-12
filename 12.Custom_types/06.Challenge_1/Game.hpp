
#pragma once
#include <SFML/Graphics.hpp>

class Game {
public:
  Game();
  void run();

private:
  void handleKeyPress(sf::Keyboard::Key key);
  void processEvents();

  sf::RenderWindow m_window;
};
