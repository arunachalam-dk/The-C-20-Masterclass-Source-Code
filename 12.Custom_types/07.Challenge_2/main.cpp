/*
  . A board that acts as a starting point for a Tetris game.
    . Board class represents the grid data.
    . BoardEntity class handles the graphical representation of the board.
    . We wire up everything in the main function.
*/
//#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

namespace {
const int WIDTH = 10; // Board width
const int HEIGHT = 20; // Board height
const float BLOCK_SIZE = 30.0f;
const std::array<sf::Color, 8> BLOCK_COLORS = {
    sf::Color::Black,      // Empty
    sf::Color::Cyan,       // I
    sf::Color::Yellow,     // O
    sf::Color(128, 0, 128),// T (Purple)
    sf::Color::Green,      // S
    sf::Color::Red,        // Z
    sf::Color::Blue,       // J
    sf::Color(255, 165, 0) // L (Orange)
};
} // namespace

// Board class represents the grid data.
class Board {
public:
    Board() : grid(HEIGHT, std::vector<int>(WIDTH, 0)) {}

    // Initialize grid with some test pattern.
    void initialize() {
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                grid[y][x] = (x + y) % BLOCK_COLORS.size();
            }
        }
    }

    const std::vector<std::vector<int>>& getGrid() const { return grid; }

private:
    std::vector<std::vector<int>> grid;
};

// BoardEntity class handles the graphical representation of the board.
class BoardEntity {
public:
    BoardEntity(const Board& board)
        : m_grid(HEIGHT, std::vector<sf::RectangleShape>(WIDTH, sf::RectangleShape(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE)))) {
        updateFromBoard(board);
    }

    void update(float /*deltaTime*/) {
        // No update logic for now.
    }

    void draw(sf::RenderWindow& window) const {
        for (const auto& row : m_grid) {
            for (const auto& cell : row) {
                window.draw(cell);
            }
        }
    }

    void updateFromBoard(const Board& board) {
        const auto& grid = board.getGrid();
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                m_grid[y][x].setPosition(x * BLOCK_SIZE, y * BLOCK_SIZE);
                m_grid[y][x].setFillColor(BLOCK_COLORS[grid[y][x]]);
                m_grid[y][x].setOutlineColor(sf::Color::White);
                m_grid[y][x].setOutlineThickness(1.0f);
            }
        }
    }

private:
    std::vector<std::vector<sf::RectangleShape>> m_grid;
};


int main() {

  // Create the SFML window.
    sf::RenderWindow window(sf::VideoMode(WIDTH * BLOCK_SIZE, HEIGHT * BLOCK_SIZE), "SFML Board Grid");

    // Create and initialize the board.
    Board board;
    board.initialize();

    // Create the BoardEntity to display the board.
    BoardEntity boardEntity(board);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window.
        window.clear();

        // Draw the board.
        boardEntity.draw(window);

        // Display the contents of the window.
        window.display();
    }

    return 0;
}