#include "PuzzleBoard.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;


void PuzzleBoard::print() {
    for (vector<char> one_line : board) {
        for (char i : one_line) {
            cout << i;
        }
        cout << endl;
    }
}

vector<char> generate_move(vector<vector<char>> board) {
    pair<int, int> white_pos = find_position(board, '0');
    vector<char> possi_move;
    if (white_pos.first != 0)
        possi_move.push_back('U');
    if (white_pos.second != 0)
        possi_move.push_back('L');
    if (white_pos.first != 2)
        possi_move.push_back('D');
    if (white_pos.second != 2)
        possi_move.push_back('R');
    return possi_move;
}

int cal_manha(vector<vector<char>> current, vector<vector<char>> goal) {
    int manhha = 0;
    pair<int, int> pos1;
    pair<int, int> pos2;
    for (char i = '1'; i <= '8'; i++) {
        pos1 = find_position(current, i);
        pos2 = find_position(goal, i);
        int diff = manha_points(pos1, pos2);
        manhha += diff;
    }
    return manhha;
}

pair<int, int> find_position(vector<vector<char>> board, char c) {
    pair<int, int> position;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (board[i][j] == c) {
                position.first = i;
                position.second = j;
            }
        }
    }
    return position;
}

int manha_points(pair<int, int> a, pair<int, int> b) {
    int i = 0;
    i += abs(a.first - b.first);
    i += abs(a.second - b.second);
    return i;
}
