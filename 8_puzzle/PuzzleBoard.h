#ifndef INC_8_PUZZLE_PUZZLEBOARD_H
#define INC_8_PUZZLE_PUZZLEBOARD_H

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int cal_manha(vector<vector<char>> current, vector<vector<char>> goal);
pair<int,int> find_position(vector<vector<char>> board, char c);
int manha_points(pair<int, int> a, pair<int, int> b);
vector<char> generate_move(vector<vector<char>> board);

class PuzzleBoard {
private:
    vector<vector<char>> board;
    int level;
    int mah_distance;
    vector<char> possible_move;
    PuzzleBoard *parent;
    char direction;
public:
    PuzzleBoard() {
        level = 0;
        parent = nullptr;
    }

    PuzzleBoard(vector<vector<char>> b_, int level_, PuzzleBoard *p_, char d_, vector<vector<char>> goal_) {
        board = b_;
        level = level_;
        parent = p_;
        direction = d_;
        mah_distance = cal_manha(board,goal_);
        possible_move = generate_move(board);
    }

    int get_Dist() {
        return mah_distance;
    }

    int get_level() {
        return level;
    }

    PuzzleBoard *get_parent() {
        return parent;
    }

    char get_direction() {
        return direction;
    }

    vector<char> get_moves() {
        return possible_move;
    }


    vector<vector<char>> get_board() {
        return board;
    }


    void print();
};

#endif //INC_8_PUZZLE_PUZZLEBOARD_H
