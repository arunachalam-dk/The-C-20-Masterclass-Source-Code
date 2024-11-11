add_library(TetrisCore
        src/Board.cpp
        src/GameState.cpp
        src/Tetromino.cpp
)

target_include_directories(TetrisCore PUBLIC include)