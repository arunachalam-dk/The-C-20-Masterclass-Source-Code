/*
        . Restructure the project into something like this : 
            /Root folder
                ├── CMakeLists.txt
                ├── assets/
                │   ├── fonts/
                │   │   └── arial.ttf
                │   └── textures/
                ├── src/
                │   ├── CMakeLists.txt
                │   ├── main.cpp
                │   ├── game/
                │   │   ├── Game.ixx
                │   │   └── GameState.ixx
                │   ├── board/
                │   │   ├── Board.ixx
                │   │   └── BoardEntity.ixx
                │   ├── pieces/
                │   │   ├── Tetromino.ixx
                │   └── utils/
                │       └── Utils.ixx

*/
import game;

int main() {
    Game game;
    game.run();
    return 0;
}