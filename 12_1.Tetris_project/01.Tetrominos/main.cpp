/*
   Step #1: 
    . A board that acts as a starting point for a Tetris game.
      . Board class represents the grid data.
      . BoardEntity class handles the graphical representation of the board.
      . We wire up everything in the main function.

   Here --> : Step2: 
    . Add a Tetromino class that represents the current falling piece.
    . Tetrominos have seven different shapes: I, O, T, S, Z, J, and L.
    . We use a 4x4 grid to represent each shape.
    . In our class, it is implemented with std::array<std::array<bool, 4>, 4> current_shape.
    . The Tetromino class has methods to move the piece left, right, down, and rotate it.
    . Integrate the Tetromino class with the Board class.
    . Add necessary utility functions to handle input and run the game loop.
*/
import utilities;

int main(){
    app();
    
}