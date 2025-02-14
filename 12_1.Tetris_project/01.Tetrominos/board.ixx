module;

#include <SFML/Graphics.hpp>
#include <array>
#include <span>

export module board;
import tetromino;

export class Board{
    public:
    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 20;
    static constexpr float BLOCK_SIZE = 30.0f;

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

    Board() {
        grid.fill({});
    }

    void initialize(){
        // Set all cells to empty (0)
        grid.fill({});
    }

    void clear_board() {
        grid.fill({});
    }

    void update_tetromino(const Tetromino& tetromino) {
        clear_board();  // Clear the board before updating

        auto shape = tetromino.get_shape();
        int type = static_cast<int>(tetromino.get_type());
        int pos_x = tetromino.get_pos_x();
        int pos_y = tetromino.get_pos_y();

        for (int y = 0; y < Tetromino::GRID_SIZE; ++y) {
            for (int x = 0; x < Tetromino::GRID_SIZE; ++x) {
                if (shape[y][x]) {
                    int board_x = pos_x + x;
                    int board_y = pos_y + y;
                    if (board_x >= 0 && board_x < WIDTH && board_y >= 0 && board_y < HEIGHT) {
                        grid[board_y][board_x] = type;
                    }
                }
            }
        }
    }

    std::span<const std::array<int, WIDTH>> get_grid() const {
        return grid;
    }

    private:
        std::array< std::array<int, WIDTH> , HEIGHT> grid; 
};


export class BoardEntity {
public:
    explicit BoardEntity(const Board& board) : board_(board) {}

    void draw(sf::RenderWindow& window) const {
        sf::RectangleShape block(sf::Vector2f(Board::BLOCK_SIZE, Board::BLOCK_SIZE));
        block.setOutlineColor(sf::Color::White);
        block.setOutlineThickness(1.0f);

        auto grid = board_.get_grid();
        for (int y = 0; y < Board::HEIGHT; ++y) {
            for (int x = 0; x < Board::WIDTH; ++x) {
                block.setPosition(x * Board::BLOCK_SIZE, y * Board::BLOCK_SIZE);
                block.setFillColor(Board::BLOCK_COLORS[grid[y][x]]);
                window.draw(block);
            }
        }
    }

private:
    const Board& board_;
};