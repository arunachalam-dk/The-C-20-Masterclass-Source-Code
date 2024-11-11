add_library(TetrisEntity
        src/Entity.cpp
        src/BoardEntity.cpp
        src/TetrominoEntity.cpp
)

target_include_directories(TetrisEntity PUBLIC include)

target_link_libraries(TetrisEntity PUBLIC sfml-graphics TetrisCore)