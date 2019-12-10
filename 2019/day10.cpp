#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;
using Input = vector<string>;
using Answer = int;

int WIDTH = 0;
int HEIGHT = 0;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    string temp;
    while (is >> temp) {
        input.push_back(temp);
    }
    is.close();

    WIDTH = input[0].size();
    HEIGHT = input.size();

    return input;
}

struct Pos {
    int row;
    int col;
    int dist2() { return row*row + col*col; };
};

int monitor_row = 0;
int monitor_col = 0;

int count_visible(int row0, int col0, Input& input) {
    unordered_set<double> found_slopes;
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (input[row][col] == '.' || (row == row0 && col == col0)) continue;
            found_slopes.insert(atan2(row - row0, col - col0));
        }
    }

    return found_slopes.size();
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 0;
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (input[row][col] == '.') continue;
            int visible = count_visible(row, col, input);
            if (visible > ans) {
                ans = visible;
                monitor_row = row;
                monitor_col = col;
            }
        }
    }
    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = 0;
    unordered_map<double, Pos> positions;
    unordered_set<double> found_slopes;
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (input[row][col] == '.' ||
                    (row == monitor_row && col == monitor_col)) continue;
            Pos pos = { -row + monitor_row, col - monitor_col };
            double angle = atan2(pos.row, pos.col);
            if (positions.count(angle)) {
                if (positions[angle].dist2() > pos.dist2()) {
                    positions[angle] = pos;
                }
            } else {
                positions[angle] = pos;
            }
            found_slopes.insert(angle);
        }
    }

    double pi = atan2(0, -1);
    vector<double> angles(found_slopes.begin(), found_slopes.end());
    for (double& angle : angles) {
        if (angle < 0) angle += 2 * pi;
    }
    sort(angles.begin(), angles.end());

    double pi2 = atan2(1, 0);
    int i = 0;
    while (angles[i] < pi2) i++;

    Pos asteroid = positions[angles[(i - 199) + angles.size()]];
    ans = (monitor_row - asteroid.row) + 100 * (monitor_col + asteroid.col);

    return ans;
}

/*
 * Run solutions.
 */
int main(int argc, char** argv) {

    Input input = get_input(argv[1]);

    auto start = chrono::high_resolution_clock::now();

    Answer first_answer = solve_first(input);
    Answer second_answer = solve_second(input);

    auto end = chrono::high_resolution_clock::now();

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();

    cout << first_answer << ", " << second_answer << " - " << elapsed << "ms" << endl;

    return 0;
}
