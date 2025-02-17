/*
   This project adds the following: 
        . Line clearing 
            . Done in the game loop in the falling logic: 
                    // Clear lines and update score
                    int lines = board.clear_complete_lines();
                    score += lines * 100; // 100 points per line
        . Score keeping
        . Game over detection
        . Visual feedback when game over and score
*/
import utilities;

int main(){
    app();
    
}