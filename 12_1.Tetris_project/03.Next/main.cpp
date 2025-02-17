/*
   This project adds the following: 
        . NOTE: Use chatgpt to generate an ascii visualization of this.
        . Next piece prediction.
            . A 6×6 block rectangle (preview_box) is drawn as the preview area.
                Positioned to the right of the main board at (Board::WIDTH + 0.5) * Board::BLOCK_SIZE.
                Filled with black, outlined in white for visibility.
            . Positioning the Tetromino in the Preview Box

                The top-left position for drawing the piece is set as:
                    preview_x = (Board::WIDTH + 1.5f) * Board::BLOCK_SIZE → Centers horizontally.
                    preview_y = 2 * Board::BLOCK_SIZE → Centers vertically.
            . Drawing the Tetromino Blocks
                Loops through the 4×4 shape array of next_piece.
                If a cell is occupied, a block (sf::RectangleShape) is drawn at:
                    preview_x + x * Board::BLOCK_SIZE
                    preview_y + y * Board::BLOCK_SIZE
                The block is colored using Board::BLOCK_COLORS based on the Tetromino type.
                White outlines are added to distinguish individual blocks.
            . Rendering in the Main Loop

                draw_next_piece(window, next_piece); is called before window.display();.
                Ensures the preview updates whenever a new piece spawns.
            
*/
import utilities;

int main(){
    app();
    
}