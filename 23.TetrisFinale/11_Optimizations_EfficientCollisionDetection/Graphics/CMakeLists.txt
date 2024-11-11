add_library(TetrisGraphics
        src/Renderer.cpp
        src/Camera.cpp
        src/TextureManager.cpp
)

target_include_directories(TetrisGraphics PUBLIC include)
target_link_libraries(TetrisGraphics PUBLIC sfml-graphics TetrisEntity)