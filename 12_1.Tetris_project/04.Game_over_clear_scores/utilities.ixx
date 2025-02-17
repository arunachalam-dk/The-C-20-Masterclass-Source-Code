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

void draw_next_piece(sf::RenderWindow& window, const Tetromino& next_piece) {
    // Draw preview box
    sf::RectangleShape preview_box;
    preview_box.setSize(sf::Vector2f(6 * Board::BLOCK_SIZE, 6 * Board::BLOCK_SIZE));
    preview_box.setPosition((Board::WIDTH + 0.5f) * Board::BLOCK_SIZE, Board::BLOCK_SIZE);
    preview_box.setFillColor(sf::Color::Black);
    preview_box.setOutlineColor(sf::Color::White);
    preview_box.setOutlineThickness(2.0f);
    
    window.draw(preview_box);
    
    float preview_x = (Board::WIDTH + 1.5f) * Board::BLOCK_SIZE;
    float preview_y = 2 * Board::BLOCK_SIZE;
    
    sf::RectangleShape block(sf::Vector2f(Board::BLOCK_SIZE, Board::BLOCK_SIZE));
    block.setOutlineColor(sf::Color::White);
    block.setOutlineThickness(1.0f);
    
    auto next_shape = next_piece.get_shape();
    int type = static_cast<int>(next_piece.get_type());
    block.setFillColor(Board::BLOCK_COLORS[type]);
    
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (next_shape[y][x]) {
                block.setPosition(preview_x + x * Board::BLOCK_SIZE,
                                preview_y + y * Board::BLOCK_SIZE);
                window.draw(block);
            }
        }
    }
}

void draw_score(sf::RenderWindow& window, int score, sf::Font& font, bool game_over) {
    sf::Text score_text;
    score_text.setFont(font);
    score_text.setCharacterSize(24);
    score_text.setFillColor(sf::Color::White);
    
    // Position below the next piece preview
    float text_x = (Board::WIDTH + 0.5f) * Board::BLOCK_SIZE;
    float text_y = 8 * Board::BLOCK_SIZE;
    
    if (game_over) {
        score_text.setString("Game Over!\nScore: " + std::to_string(score) + "\nPress R to restart");
    } else {
        score_text.setString("Score: " + std::to_string(score));
    }
    
    score_text.setPosition(text_x, text_y);
    window.draw(score_text);
}

export void app() {
    sf::RenderWindow window(sf::VideoMode((Board::WIDTH + 7) * Board::BLOCK_SIZE, 
                            Board::HEIGHT * Board::BLOCK_SIZE), 
                            "Tetris");
    window.setFramerateLimit(60);
    
    Board board;
    BoardEntity entity(board);
    Tetromino current_piece(spawn_new_tetromino());
    Tetromino next_piece(spawn_new_tetromino());
    bool game_over = false;
    int score = 0;

    sf::Clock movement_clock;
    sf::Clock fall_clock;
    const float move_delay = 0.1f;    // Delay between movements
    const float fall_delay = 0.5f;    // Time between falls: bring this down to increase speed

    board.initialize();

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Error loading font\n";
        return;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && game_over) {
                if (event.key.code == sf::Keyboard::R) {
                    // Reset game
                    board.clear_board();
                    current_piece = spawn_new_tetromino();
                    next_piece = spawn_new_tetromino();
                    game_over = false;
                    score = 0;
                }
            }
        }

        if (!game_over) {
            // Input handling with delay. The delay ensures that keypresses do not register 
            // too frequently when a player holds down a movement key. Without it, pressing 
            // and holding a key would move the piece too quickly, making the game unplayable.
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
            if (fall_clock.getElapsedTime().asSeconds() >= fall_delay) {
                current_piece.backup_position();
                current_piece.move_down();
                
                if (board.is_collision(current_piece)) {
                    //Brind the piece back to its previous position, if it falls our of range
                    current_piece.undo_move();

                    //Lock it in place
                    board.lock_current_piece(current_piece);
                    
                    // Clear lines and update score
                    int lines = board.clear_complete_lines();
                    score += lines * 100; // 100 points per line
                    
                    // Get next piece and check for game over
                    current_piece = next_piece;
                    next_piece = spawn_new_tetromino();
                    
                    if (board.is_game_over(current_piece)) {
                        game_over = true;
                    }
                }
                
                fall_clock.restart();
            }
        }

        board.update_tetromino(current_piece);
        
        window.clear(sf::Color::Black);
        entity.draw(window);
        draw_next_piece(window, next_piece);
        draw_score(window, score, font, game_over);
        
        window.display();
    }
}