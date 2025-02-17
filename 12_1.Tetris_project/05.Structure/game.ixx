module;
#include <SFML/Graphics.hpp>

export module game;
import board;
import tetromino;
import utilities;

export class Game {
private:
    sf::RenderWindow window;
    Board board;
    BoardEntity entity;
    Tetromino current_piece;
    Tetromino next_piece;
    bool game_over;
    int score;
    sf::Font font;
    sf::Clock movement_clock;
    sf::Clock fall_clock;
    const float move_delay = 0.1f;
    const float fall_delay = 0.5f;

public:
    Game() : window(sf::VideoMode((Board::WIDTH + 7) * Board::BLOCK_SIZE, 
                   Board::HEIGHT * Board::BLOCK_SIZE), "Tetris"),
             board(),
             entity(board),
             current_piece(spawn_new_tetromino()),
             next_piece(spawn_new_tetromino()),
             game_over(false),
             score(0) {
        window.setFramerateLimit(60);
        board.initialize();
        if (!font.loadFromFile("arial.ttf")) {
            throw std::runtime_error("Error loading font");
        }
    }

    void run() {
        while (window.isOpen()) {
            handle_events();
            update();
            render();
        }
    }

private:
    void handle_events() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && game_over) {
                if (event.key.code == sf::Keyboard::R) {
                    reset_game();
                }
            }
        }
    }

    void update() {
        if (!game_over) {
            handle_input();
            handle_falling();
        }
    }

    void render() {
        window.clear(sf::Color::Black);
        entity.draw(window);
        draw_next_piece(window, next_piece);
        draw_score(window, score, font, game_over);
        window.display();
    }

    void handle_input() {
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
    }

    void handle_falling() {
        if (fall_clock.getElapsedTime().asSeconds() >= fall_delay) {
            current_piece.backup_position();
            current_piece.move_down();
            
            if (board.is_collision(current_piece)) {
                current_piece.undo_move();
                board.lock_current_piece(current_piece);
                
                int lines = board.clear_complete_lines();
                score += lines * 100;
                
                current_piece = next_piece;
                next_piece = spawn_new_tetromino();
                
                if (board.is_game_over(current_piece)) {
                    game_over = true;
                }
            }
            
            fall_clock.restart();
        }
        board.update_tetromino(current_piece);
    }

    void reset_game() {
        board.clear_board();
        current_piece = spawn_new_tetromino();
        next_piece = spawn_new_tetromino();
        game_over = false;
        score = 0;
    }
};
