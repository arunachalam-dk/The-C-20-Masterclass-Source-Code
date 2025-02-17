/*
   This projects adds the following: 
    . Collision and bound detection in the board module.
        . see functions: 
            . is_collision
            . is_out_of_bounds
    . Locking of pieces in the board module. This is needed when a piece reaches the 
        bottom of the board or collides with another piece.
        . We maintain a grid of bools to keep track of locked pieces.
        . see function:
            . lock_current_piece

    . A way to back up from a wrong move. This is done by keeping a copy of the tetromino
        around.
        . see tetromino class:
            . backup_position
            . undo_move

    . Automatic falling in the utilities module
        .The move delay (move_delay = 0.1f;) ensures that keypresses do not register too frequently when a player holds down a movement key. Without it, pressing and holding a key would move the piece too quickly, making the game unplayable.

        . The fall delay (fall_delay = 0.5f;) controls how often the tetromino automatically falls down. This ensures that pieces move downward at a predictable speed, rather than instantly dropping to the bottom.
*/
import utilities;

int main(){
    app();
    
}