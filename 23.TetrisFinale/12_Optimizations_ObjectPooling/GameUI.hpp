#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "TextureManager.hpp"

class GameUI {
public:
  GameUI();
  void update(const GameState& gameState);
  void draw(sf::RenderWindow& window);
  void showGameOver();
  void showPaused();

private:
  int m_score;
  int m_level;
  Tetromino::Type m_nextPieceType;
  bool m_isGameOver;
  bool m_isPaused;

  sf::RectangleShape m_nextPiecePreview;
  std::vector<sf::RectangleShape> m_nextPieceBlocks;

  void updateScoreText(int score);
  void updateLevelText(int level);
  void updateNextPiecePreview(Tetromino::Type nextPieceType);
  void drawNextPiece(sf::RenderWindow& window);
};