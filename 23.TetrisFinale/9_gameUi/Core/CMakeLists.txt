add_library(TetrisCore
        src/Board.cpp
        src/GameState.cpp
        src/Tetromino.cpp
        src/RandomGenerator.cpp
        src/ScoreManager.cpp
)

target_include_directories(TetrisCore PUBLIC include)
target_link_libraries(TetrisCore PRIVATE)