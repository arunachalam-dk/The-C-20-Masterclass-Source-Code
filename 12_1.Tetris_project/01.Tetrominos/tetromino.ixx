module;

#include <array>
#include <algorithm>

export module tetromino;

export class Tetromino {
public:
    enum Type { I = 1, O, T, S, Z, J, L };
    static constexpr int GRID_SIZE = 4;

    Tetromino(Type type) : current_type(type), current_rotation(0), pos_x(3), pos_y(0) {
        initialize_shape(type);
    }

    void move_left() { --pos_x; }
    void move_right() { ++pos_x; }
    void move_down() { ++pos_y; }

    //When you rotate a 4×4 matrix clockwise, every element at position (i, j) moves to (j, 3 - i)
    void rotate() {
        std::array<std::array<bool, GRID_SIZE>, GRID_SIZE> temp = current_shape;
        
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                current_shape[j][GRID_SIZE-1-i] = temp[i][j];
            }
        }
        current_rotation = (current_rotation + 1) % 4;
    }

    int get_pos_x() const { return pos_x; }
    int get_pos_y() const { return pos_y; }
    Type get_type() const { return current_type; }
    const auto& get_shape() const { return current_shape; }

private:
    void initialize_shape(Type type) {
        current_shape.fill({});
        switch (type) {
            case I:
                current_shape[1] = {true, true, true, true};
                break;
            case O:
                current_shape[1][1] = current_shape[1][2] = 
                current_shape[2][1] = current_shape[2][2] = true;
                break;
            case T:
                current_shape[1] = {true, true, true, false};
                current_shape[2][1] = true;
                break;
            case S:
                current_shape[1] = {false, true, true, false};
                current_shape[2] = {true, true, false, false};
                break;
            case Z:
                current_shape[1] = {true, true, false, false};
                current_shape[2] = {false, true, true, false};
                break;
            case J:
                current_shape[1] = {true, true, true, false};
                current_shape[2][0] = true;
                break;
            case L:
                current_shape[1] = {true, true, true, false};
                current_shape[2][2] = true;
                break;
        }
    }

    Type current_type;
    int current_rotation;
    int pos_x;
    int pos_y;
    std::array<std::array<bool, GRID_SIZE>, GRID_SIZE> current_shape;
};
