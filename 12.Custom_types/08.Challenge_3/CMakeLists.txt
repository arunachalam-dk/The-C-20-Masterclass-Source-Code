cmake_minimum_required(VERSION 3.28)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(
        TetrisSFML
        VERSION 0.0.1
        DESCRIPTION "Tetris Game using SFML"
        LANGUAGES CXX C)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

find_package(fmt CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

add_executable(Tetris
        main.cpp
)

target_link_libraries(Tetris PRIVATE sfml-graphics )