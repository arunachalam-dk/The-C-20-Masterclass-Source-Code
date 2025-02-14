module;
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

export module utilities;
import board;
import tetromino;

Tetromino spawn_new_tetromino() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 7);
    return Tetromino(static_cast<Tetromino::Type>(dis(gen)));
}

export void app() {
    sf::RenderWindow window(sf::VideoMode(Board::WIDTH * Board::BLOCK_SIZE, 
                            Board::HEIGHT * Board::BLOCK_SIZE), 
                            "Tetris");
    window.setFramerateLimit(60);
    
    Board board;
    BoardEntity entity(board);
    Tetromino current_piece(Tetromino::Type::T);
    bool piece_locked = false;

    sf::Clock movement_clock;
    sf::Clock fall_clock;
    const float move_delay = 0.1f;    // Delay between movements
    const float fall_delay = 0.5f;    // Time between falls
    bool falling = true;

    board.initialize();

    while (window.isOpen()) {
        // Window events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Input handling with delay
        if (movement_clock.getElapsedTime().asSeconds() >= move_delay) {
            current_piece.backup_position();
            bool moved = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                current_piece.move_left();
                moved = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                current_piece.move_right();
                moved = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                current_piece.move_down();
                moved = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                current_piece.rotate();
                moved = true;
            }

            if (moved) {
                if (board.is_collision(current_piece)) {
                    current_piece.undo_move();
                }
                movement_clock.restart();
            }
        }

        // Automatic falling
        if (falling && fall_clock.getElapsedTime().asSeconds() >= fall_delay) {
            current_piece.backup_position();
            current_piece.move_down();
            
            if (board.is_collision(current_piece)) {
                current_piece.undo_move();
                board.lock_current_piece(current_piece);
                current_piece = spawn_new_tetromino();
                std::cout << "Spawned new piece\n";  // Debug output
            }
            
            fall_clock.restart();
        }

        board.update_tetromino(current_piece);
        
        window.clear(sf::Color::Black);
        entity.draw(window);
        window.display();
    }
}