/*
  . A board that acts as a starting point for a Tetris game.
    . Board class represents the grid data.
    . BoardEntity class handles the graphical representation of the board.
    . We wire up everything in the main function.
*/

#include <SFML/Graphics.hpp>
#include <array>
#include <span>

class Board {
public:
    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 20;
    static constexpr float BLOCK_SIZE = 30.0f;
    // Changed from constexpr to inline static const.
    inline static const std::array<sf::Color, 8> BLOCK_COLORS = {
        sf::Color::Black,      // Empty
        sf::Color::Cyan,       // I
        sf::Color::Yellow,     // O
        sf::Color(128, 0, 128),// T (Purple)
        sf::Color::Green,      // S
        sf::Color::Red,        // Z
        sf::Color::Blue,       // J
        sf::Color(255, 165, 0) // L (Orange)
    };

    Board() { grid.fill({}); }

    void initialize() {
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                grid[y][x] = (x + y) % BLOCK_COLORS.size();
            }
        }
    }

    std::span<const std::array<int, WIDTH>> getGrid() const { return grid; }

private:
    std::array<std::array<int, WIDTH>, HEIGHT> grid;
};

class BoardEntity {
public:
    explicit BoardEntity(const Board& board) : m_board(board) {}

    void draw(sf::RenderWindow& window) const {
        sf::RectangleShape block(sf::Vector2f(Board::BLOCK_SIZE, Board::BLOCK_SIZE));
        block.setOutlineColor(sf::Color::White);
        block.setOutlineThickness(1.0f);

        auto grid = m_board.getGrid();
        for (int y = 0; y < Board::HEIGHT; ++y) {
            for (int x = 0; x < Board::WIDTH; ++x) {
                block.setPosition(x * Board::BLOCK_SIZE, y * Board::BLOCK_SIZE);
                block.setFillColor(Board::BLOCK_COLORS[grid[y][x]]);
                window.draw(block);
            }
        }
    }

private:
    const Board& m_board;
};

void handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(Board::WIDTH * Board::BLOCK_SIZE, 
                            Board::HEIGHT * Board::BLOCK_SIZE), 
                            "SFML Board Grid");
    Board board;
    board.initialize();
    BoardEntity boardEntity(board);

    while (window.isOpen()) {
        handleInput(window);
        window.clear();
        boardEntity.draw(window);
        window.display();
    }
    return 0;
}
