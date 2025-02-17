find_package(fmt CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_sources(${PROJECT_NAME}
    PUBLIC
    FILE_SET CXX_MODULES FILES
    board/board.ixx 
    board/board_entity.ixx 
    game/game.ixx 
    game/gamestate.ixx 
    pieces/tetromino.ixx 
    utils/utilities.ixx 
)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt sfml-graphics)
