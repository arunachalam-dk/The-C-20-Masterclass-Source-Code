/*
   Step #1: 
    . A board that acts as a starting point for a Tetris game.
      . Board class represents the grid data.
      . BoardEntity class handles the graphical representation of the board.
      . We wire up everything in the main function.

   Here --> : Step2: 
    . ATTENTION: Make sure you understand how the tetroiminos are drawn on the board.
    . Add a Tetromino class that represents the current falling piece.
    . Tetrominos have seven different shapes: I, O, T, S, Z, J, and L.
    . We use a 4x4 grid to represent each shape.
    . In our class, it is implemented with std::array<std::array<bool, 4>, 4> current_shape.
    . The Tetromino class has methods to move the piece left, right, down, and rotate it.
    . Integrate the Tetromino class with the Board class.
    . The important thing to understand here is how local coordintates from a tetromino are mapped to the global coordinates of the board.
        . Assuming we start with a T tetromino at position (3, 0) on the board, as per our defaults, the tetromino will be drawn as follows in its local coordinates: 

            . . . .
            T T T .
            . T . .
            . . . .

        . The turned on coordinates are shown below in a list: 
            (0, 1)
            (1, 1) 
            (2, 1) 
            (1, 2)

        . In the board, we want to position the tetromino starting at position (3, 0). We need to figure out which boxes
            to turn on in the board grid. We do this by adding the local coordinates of the tetromino to the position of the tetromino on the board.
            The global coordinates of the tetromino on the board are: 
                (3, 0) + (0, 1) = (3, 1)
                (3, 0) + (1, 1) = (4, 1)
                (3, 0) + (2, 1) = (5, 1)
                (3, 0) + (1, 2) = (4, 2)

        . Following this logid, the first tetromino will be drawn as follows on the board:

            . . . . . . . . . .
            . . . T T T . . . .
            . . . . T . . . . .
            . . . . . . . . . .
            . . . . . . . . . .






    
*/
import utilities;

int main(){
    app();
    
}