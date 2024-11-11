#include "RandomGenerator.hpp"
#include <chrono>

RandomGenerator::RandomGenerator()
    : rng(std::chrono::system_clock::now().time_since_epoch().count()),
      dist(0, 6) {}

Tetromino::Type RandomGenerator::getNextType() {
  return static_cast<Tetromino::Type>(dist(rng));
}