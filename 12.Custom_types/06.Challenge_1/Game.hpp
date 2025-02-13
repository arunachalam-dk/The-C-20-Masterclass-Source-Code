
#pragma once
#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    void handle_key_press(sf::Keyboard::Key key);
    void process_events();

    sf::RenderWindow window_;
};