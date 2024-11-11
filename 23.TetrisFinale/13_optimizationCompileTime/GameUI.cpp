#include "GameUI.hpp"

namespace {
    constexpr float BLOCK_SIZE = 20.0f;
    const sf::Vector2f NEXT_PIECE_POSITION(550.0f, 200.0f);
    const std::array<sf::Color, 7> TETROMINO_COLORS = {
        sf::Color::Cyan,   // I
        sf::Color::Yellow, // O
        sf::Color(128, 0, 128),  // T (Purple)
        sf::Color::Green,  // S
        sf::Color::Red,    // Z
        sf::Color::Blue,   // J
        sf::Color(255, 165, 0)   // L (Orange)
    };
}

GameUI::GameUI()
    : m_score(0)
    , m_level(1)
    , m_nextPieceType(Tetromino::Type::I)
    , m_isGameOver(false)
    , m_isPaused(false)
{
    m_nextPiecePreview.setSize(sf::Vector2f(5 * BLOCK_SIZE, 5 * BLOCK_SIZE));
    m_nextPiecePreview.setPosition(NEXT_PIECE_POSITION);
    m_nextPiecePreview.setFillColor(sf::Color::Black);
    m_nextPiecePreview.setOutlineColor(sf::Color::White);
    m_nextPiecePreview.setOutlineThickness(2);
}

void GameUI::update(const GameState& gameState) {
    updateScoreText(gameState.getScoreManager().getScore());
    updateLevelText(gameState.getScoreManager().getLevel());
    updateNextPiecePreview(gameState.getNextTetromino().getType());
}

void GameUI::draw(sf::RenderWindow& window) {
    TextureManager& textureManager = TextureManager::getInstance();

    textureManager.drawText("Score: " + std::to_string(m_score), 550, 50, window);
    textureManager.drawText("Level: " + std::to_string(m_level), 550, 100, window);
    textureManager.drawText("Next Piece:", 550, 150, window);

    window.draw(m_nextPiecePreview);
    drawNextPiece(window);

    if (m_isGameOver) {
        textureManager.drawText("GAME OVER", 300, 250, window);
        textureManager.drawText("Press Enter to restart", 250, 300, window);
    }

    if (m_isPaused) {
        textureManager.drawText("PAUSED", 350, 250, window);
        textureManager.drawText("Press P to resume", 300, 300, window);
    }
}

void GameUI::showGameOver() {
    m_isGameOver = true;
}

void GameUI::showPaused() {
    m_isPaused = !m_isPaused;
}

void GameUI::updateScoreText(int score) {
    m_score = score;
}

void GameUI::updateLevelText(int level) {
    m_level = level;
}

void GameUI::updateNextPiecePreview(Tetromino::Type nextPieceType) {
    m_nextPieceType = nextPieceType;
    m_nextPieceBlocks.clear();

    std::vector<sf::Vector2i> shape;
    switch (m_nextPieceType) {
        case Tetromino::Type::I:
            shape = {{0,1}, {1,1}, {2,1}, {3,1}};
            break;
        case Tetromino::Type::O:
            shape = {{0,0}, {1,0}, {0,1}, {1,1}};
            break;
        case Tetromino::Type::T:
            shape = {{1,0}, {0,1}, {1,1}, {2,1}};
            break;
        case Tetromino::Type::S:
            shape = {{1,0}, {2,0}, {0,1}, {1,1}};
            break;
        case Tetromino::Type::Z:
            shape = {{0,0}, {1,0}, {1,1}, {2,1}};
            break;
        case Tetromino::Type::J:
            shape = {{0,0}, {0,1}, {1,1}, {2,1}};
            break;
        case Tetromino::Type::L:
            shape = {{2,0}, {0,1}, {1,1}, {2,1}};
            break;
    }

    for (const auto& pos : shape) {
        sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
        block.setPosition(NEXT_PIECE_POSITION.x + pos.x * BLOCK_SIZE,
                          NEXT_PIECE_POSITION.y + pos.y * BLOCK_SIZE);
        block.setFillColor(TETROMINO_COLORS[static_cast<int>(m_nextPieceType)]);
        block.setOutlineColor(sf::Color::White);
        block.setOutlineThickness(1);
        m_nextPieceBlocks.push_back(block);
    }
}

void GameUI::drawNextPiece(sf::RenderWindow& window) {
    for (const auto& block : m_nextPieceBlocks) {
        window.draw(block);
    }
}