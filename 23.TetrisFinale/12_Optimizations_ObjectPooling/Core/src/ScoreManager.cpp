#include "ScoreManager.hpp"

ScoreManager::ScoreManager() : score(0), level(1), linesCleared(0) {}

void ScoreManager::addScore(int clearedLines) {
  switch (clearedLines) {
  case 1:
    score += 100 * level;
    break;
  case 2:
    score += 300 * level;
    break;
  case 3:
    score += 500 * level;
    break;
  case 4:
    score += 800 * level;
    break;
  }

  linesCleared += clearedLines;
  level = 1 + (linesCleared / 10);
}