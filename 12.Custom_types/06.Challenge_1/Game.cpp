
#include <iostream>
#include "Game.hpp"
Game::Game() : window_{sf::VideoMode(800, 600), "Tetris"} {}

void Game::run()
{
    while (window_.isOpen()) {
        process_events(); // Handle user input
    }
}

void Game::handle_key_press(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::K) {
        std::cout << "K key pressed!" << std::endl;
    }
}

void Game::process_events()
{
    sf::Event event;
    while (window_.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window_.close();
            break;
        case sf::Event::KeyPressed:
            handle_key_press(event.key.code);
            break;
        default:
            break;
        }
    }
}
