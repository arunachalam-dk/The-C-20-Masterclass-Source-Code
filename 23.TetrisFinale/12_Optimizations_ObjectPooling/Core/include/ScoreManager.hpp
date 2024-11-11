#pragma once

class ScoreManager {
public:
  ScoreManager();
  void addScore(int clearedLines);
  int getScore() const { return score; }
  int getLevel() const { return level; }
  int getLinesCleared() const { return linesCleared; }

private:
  int score;
  int level;
  int linesCleared;
};