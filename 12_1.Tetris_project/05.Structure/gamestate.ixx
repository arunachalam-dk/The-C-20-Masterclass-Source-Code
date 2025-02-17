module;
#include <SFML/Graphics.hpp>

export module gamestate;
import board;
import tetromino;
import utilities;

export class GameState {
public:
    GameState() 
        : board_()
        , current_piece_(spawn_new_tetromino())
        , next_piece_(spawn_new_tetromino())
        , game_over_(false)
        , score_(0) {
        board_.initialize();
    }

    void update(float delta_time) {
        if (!game_over_) {
            handle_falling(delta_time);
        }
    }

    void move_left() {
        if (game_over_) return;
        current_piece_.backup_position();
        current_piece_.move_left();
        if (board_.is_collision(current_piece_)) {
            current_piece_.undo_move();
        }
    }

    void move_right() {
        if (game_over_) return;
        current_piece_.backup_position();
        current_piece_.move_right();
        if (board_.is_collision(current_piece_)) {
            current_piece_.undo_move();
        }
    }

    void move_down() {
        if (game_over_) return;
        current_piece_.backup_position();
        current_piece_.move_down();
        if (board_.is_collision(current_piece_)) {
            current_piece_.undo_move();
        }
    }

    void rotate() {
        if (game_over_) return;
        current_piece_.backup_position();
        current_piece_.rotate();
        if (board_.is_collision(current_piece_)) {
            current_piece_.undo_move();
        }
    }

    void reset() {
        board_.clear_board();
        current_piece_ = spawn_new_tetromino();
        next_piece_ = spawn_new_tetromino();
        game_over_ = false;
        score_ = 0;
    }

    // Getters
    const Board& get_board() const { return board_; }
    const Tetromino& get_current_piece() const { return current_piece_; }
    const Tetromino& get_next_piece() const { return next_piece_; }
    bool is_game_over() const { return game_over_; }
    int get_score() const { return score_; }

private:
    void handle_falling(float delta_time) {
        falling_time_ += delta_time;
        if (falling_time_ >= fall_delay_) {
            current_piece_.backup_position();
            current_piece_.move_down();
            
            if (board_.is_collision(current_piece_)) {
                current_piece_.undo_move();
                board_.lock_current_piece(current_piece_);
                
                int lines = board_.clear_complete_lines();
                score_ += lines * 100;
                
                current_piece_ = next_piece_;
                next_piece_ = spawn_new_tetromino();
                
                if (board_.is_game_over(current_piece_)) {
                    game_over_ = true;
                }
            }
            
            falling_time_ = 0;
        }
        board_.update_tetromino(current_piece_);
    }

    Board board_;
    Tetromino current_piece_;
    Tetromino next_piece_;
    bool game_over_;
    int score_;
    float falling_time_ = 0;
    const float fall_delay_ = 0.5f;
};
