add_library(TetrisCore
        src/Board.cpp
        src/GameState.cpp
)

target_include_directories(TetrisCore PUBLIC include)