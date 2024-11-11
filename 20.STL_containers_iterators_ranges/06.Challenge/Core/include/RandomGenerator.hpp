#pragma once
#include <random>
#include "Tetromino.hpp"

class RandomGenerator {
public:
  RandomGenerator();
  Tetromino::Type getNextType();

private:
  std::mt19937 rng;
  std::uniform_int_distribution<> dist;
};