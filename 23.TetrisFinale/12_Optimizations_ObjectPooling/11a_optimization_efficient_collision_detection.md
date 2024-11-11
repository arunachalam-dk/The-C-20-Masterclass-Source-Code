# Efficient collision detection:
The current collision detection in the Board class checks each block of a tetromino against the board. This could be optimized by:
1. Using a bounding box check first before checking individual blocks
2. Implementing a spatial partitioning system (e.g., grid-based) to reduce the number of checks

Let's get to it. 

Let's update the `Tetromino` class to include a bounding box:

```c++
// In Tetromino.hpp
#include <array>
#include <span>
#include <algorithm>

class Tetromino {
public:
    // ... existing code ...

    struct BoundingBox {
        int left, right, top, bottom;
    };

    [[nodiscard]] BoundingBox getBoundingBox() const noexcept {
        auto [minX, maxX] = std::ranges::minmax_element(blocks, {}, [](const auto& b) { return b[0]; });
        auto [minY, maxY] = std::ranges::minmax_element(blocks, {}, [](const auto& b) { return b[1]; });
        return {minX->at(0), maxX->at(0), minY->at(1), maxY->at(1)};
    }

    // ... existing code ...
};
```

Now, let's update the `Board` class to use this new bounding box for collision detection:

```c++
// In Board.hpp
#include <span>
#include <ranges>
#include <algorithm>

class Board {
public:
    // ... existing code ...

    [[nodiscard]] bool isCollision(const Tetromino& tetromino) const noexcept {
        auto bb = tetromino.getBoundingBox();
        
        // Bounding box check
        if (bb.left < 0 || bb.right >= WIDTH || bb.bottom >= HEIGHT) {
            return true;
        }

        // If bounding box overlaps with non-empty cells, do a detailed check
        if (bb.top >= 0 && hasNonEmptyCells(bb)) {
            return detailedCollisionCheck(tetromino);
        }

        return false;
    }

private:
    // ... existing code ...

    [[nodiscard]] bool hasNonEmptyCells(const Tetromino::BoundingBox& bb) const noexcept {
        return std::ranges::any_of(std::views::iota(std::max(0, bb.top), std::min(HEIGHT, bb.bottom + 1)),
            [this, &bb](int y) {
                return std::ranges::any_of(std::views::iota(bb.left, bb.right + 1),
                    [this, y](int x) { return grid[y][x] != 0; });
            });
    }

    [[nodiscard]] bool detailedCollisionCheck(const Tetromino& tetromino) const noexcept {
        return std::ranges::any_of(tetromino.getBlocks(), [this](const auto& block) {
            int x = block[0];
            int y = block[1];
            return y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH && grid[y][x] != 0;
        });
    }
};
```

Changes: 

1. We've added a `BoundingBox` struct to the `Tetromino` class to represent its boundaries.

2. The `getBoundingBox()` method uses `std::ranges::minmax_element` to efficiently find the boundaries of the tetromino.

3. In the `Board` class, we've updated `isCollision()` to first perform a bounding box check, which is faster than checking each block individually.

4. We use `[[nodiscard]]` to ensure that the return values of our boolean functions are not accidentally ignored.

5. The `hasNonEmptyCells()` method uses C++23's `std::views::iota` to create a range of integers for our loops, allowing for a more functional programming style.

6. We use `std::ranges::any_of` in both `hasNonEmptyCells()` and `detailedCollisionCheck()` to check for collisions in a concise and efficient manner.

7. The `detailedCollisionCheck()` method is only called if the bounding box overlaps with non-empty cells, reducing unnecessary checks.

