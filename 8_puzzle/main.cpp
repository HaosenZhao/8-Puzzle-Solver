#include "PuzzleBoard.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <set>
#include <ctime>

using namespace std;

vector<vector<char>> read_board(string file_name) {
    ifstream in_file;
    in_file.open(file_name);
    stringstream str_stream;
    str_stream << in_file.rdbuf();
    string str = str_stream.str();
    vector<vector<char>> new_board;
    stringstream ss(str);
    string one_line_str;
    while (getline(ss, one_line_str, '\n')) {
        vector<char> one_line;
        for (char i : one_line_str) {
            one_line.push_back(i);
        }
        new_board.push_back(one_line);
    }
    return new_board;
}

struct ComparePointer {
    bool operator()(PuzzleBoard * p1, PuzzleBoard *p2) {
        return p1->get_level() + p1->get_Dist() > p2->get_level() + p2->get_Dist();
    }
};

set<vector<vector<char>>> visited;
priority_queue<PuzzleBoard*, vector<PuzzleBoard*>, ComparePointer> my_queue;
vector<vector<char>> goal_state = read_board("goal.txt");

vector<vector<char>> generate_board(PuzzleBoard currentState, char direction) {
    vector<vector<char>> new_board = currentState.get_board();
    pair<int, int> white_loc = find_position(new_board, '0');
    if (direction == 'U') {
        new_board[white_loc.first][white_loc.second] = new_board[white_loc.first - 1][white_loc.second];
        new_board[white_loc.first - 1][white_loc.second] = '0';
    } else if (direction == 'D') {
        new_board[white_loc.first][white_loc.second] = new_board[white_loc.first + 1][white_loc.second];
        new_board[white_loc.first + 1][white_loc.second] = '0';
    } else if (direction == 'L') {
        new_board[white_loc.first][white_loc.second] = new_board[white_loc.first][white_loc.second - 1];
        new_board[white_loc.first][white_loc.second - 1] = '0';
    } else {
        new_board[white_loc.first][white_loc.second] = new_board[white_loc.first][white_loc.second + 1];
        new_board[white_loc.first][white_loc.second + 1] = '0';
    }
    return new_board;
}

vector<char> explore() {
    clock_t begin = clock();

    vector<char> direction_lst;
    int counter = 1;
    while (my_queue.size() != 0) {
        PuzzleBoard* toMove = my_queue.top();
        my_queue.pop();
        if (toMove->get_Dist() == 0) {
            while (toMove->get_parent() != nullptr) {
                direction_lst.push_back(toMove->get_direction());
                toMove = toMove->get_parent();
            }

            clock_t end = clock();
            double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
            cout << "it spend " << elapsed_secs << "s to finish the explore!" << endl;
            cout << "Nodes generated: " << counter << endl;
            return direction_lst;
        }

        for (char direction : toMove->get_moves()) {
            vector<vector<char>> board = generate_board(*toMove, direction);
            if (visited.find(board) == visited.end()) {
                PuzzleBoard *generated = new PuzzleBoard(board, toMove->get_level() + 1, toMove, direction, goal_state);
                visited.insert(board);
                counter++;
                my_queue.push(generated);
            }
        }
    }
    return direction_lst;
}


int main() {
    PuzzleBoard* initial_board = new PuzzleBoard(read_board("ini_board.txt"), 0, nullptr, '0', goal_state);
    if (initial_board->get_Dist() == 0)
        cout << "it's the goal state already!" << endl;
    my_queue.push(initial_board);
    visited.insert(initial_board->get_board());

    vector<char> trace = explore();
    reverse(trace.begin(),trace.end());
    for (char c:trace) {
        cout << c ;
    }
    return 0;
}