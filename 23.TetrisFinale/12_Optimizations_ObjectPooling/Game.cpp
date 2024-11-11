#include "Game.hpp"

Game::Game()
    : m_window(sf::VideoMode(800, 600), "TetrisSFML")
    , m_renderer(m_window)
    , m_camera(800.f, 600.f)
    , m_currentTetrominoEntity(m_gameState.getCurrentTetromino())
    , m_ghostPieceEntity(m_gameState.getCurrentTetromino(), m_gameState.getBoard())
    , m_boardEntity(m_gameState.getBoard())
    , m_gameMode(GameMode::Playing)
    , m_deltaTime(0.f)
{
    initializeGame();
}

void Game::run() {
    while (m_window.isOpen()) {
        m_deltaTime = m_clock.restart().asSeconds();

        processEvents();
        update(m_deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            handleKeyPress(event.key.code);
        }
    }
}

void Game::update(float deltaTime) {
    if (m_gameMode == GameMode::Playing) {
        m_gameState.update(deltaTime);
        updateEntities();
        m_gameUI.update(m_gameState);
        checkGameOver();
    }
}

void Game::render() {
    m_renderer.beginDraw();

    m_boardEntity.draw(m_window);
    m_ghostPieceEntity.draw(m_window);
    m_currentTetrominoEntity.draw(m_window);
    m_gameUI.draw(m_window);

    m_renderer.endDraw();
}

void Game::initializeGame() {
    // Set up the window
    m_window.setFramerateLimit(60);

    // Initialize the camera
    m_camera.setCenter(sf::Vector2f(400, 300));
    m_renderer.setView(m_camera);

    // Load textures
    TextureManager& textureManager = TextureManager::getInstance();
    /*if (!textureManager.loadTexture("block", "assets/block.png")) {
        throw std::runtime_error("Failed to load block texture");
    }*/
    if (!textureManager.loadFont("default", "Res/Images/Font.png")) {
        throw std::runtime_error("Failed to load default font");
    }

    // Set up the game board
    m_boardEntity.setPosition(sf::Vector2f(50, 50));

    // Initialize game state
    resetGame();
}

void Game::handleKeyPress(sf::Keyboard::Key key) {
    if (m_gameMode == GameMode::Playing) {
        switch (key) {
            case sf::Keyboard::Left:
                m_gameState.moveTetromino(-1);
                break;
            case sf::Keyboard::Right:
                m_gameState.moveTetromino(1);
                break;
            case sf::Keyboard::Down:
                m_gameState.softDrop();
                break;
            case sf::Keyboard::Up:
                m_gameState.rotateTetromino();
                break;
            case sf::Keyboard::Space:
                m_gameState.hardDrop();
                break;
            case sf::Keyboard::P:
                m_gameMode = GameMode::Paused;
                m_gameUI.showPaused();
                break;
        }
    } else if (m_gameMode == GameMode::Paused) {
        if (key == sf::Keyboard::P) {
            m_gameMode = GameMode::Playing;
            m_gameUI.showPaused(); // Toggle off pause display
        }
    } else if (m_gameMode == GameMode::GameOver) {
        if (key == sf::Keyboard::Enter) {
            resetGame();
        }
    }
}

void Game::updateEntities() {
    m_currentTetrominoEntity.updateFromTetromino(m_gameState.getCurrentTetromino());
    m_ghostPieceEntity.updatePosition(m_gameState.getCurrentTetromino(), m_gameState.getBoard());
    m_boardEntity.updateFromBoard(m_gameState.getBoard());
}

void Game::checkGameOver() {
    if (m_gameState.isGameOver()) {
        m_gameMode = GameMode::GameOver;
        m_gameUI.showGameOver();
    }
}

void Game::resetGame() {
    m_gameState = GameState();
    m_currentTetrominoEntity.updateFromTetromino(m_gameState.getCurrentTetromino());
    m_ghostPieceEntity.updatePosition(m_gameState.getCurrentTetromino(), m_gameState.getBoard());
    m_boardEntity.updateFromBoard(m_gameState.getBoard());
    m_gameMode = GameMode::Playing;
    m_gameUI = GameUI();
}