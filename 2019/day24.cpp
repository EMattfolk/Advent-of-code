#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;
using Input = vector<string>;
using Answer = int;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    string temp;
    while (is >> temp) input.push_back(temp);
    is.close();

    return input;
}

string concat(vector<string>& state) {
    string res = "";
    for (string& row : state) {
        res += row;
    }

    return res;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    unordered_set<string> states;
    vector<string> state = input;
    while (states.count(concat(state)) == 0) {
        states.insert(concat(state));
        vector<string> new_state = state;
        for (uint32_t i = 0; i < state.size(); i++) {
            for (uint32_t j = 0; j < state.size(); j++) {
                int neighbors = 0;
                if (i > 0) {
                    neighbors += state[i-1][j] == '#';
                }
                if (i < state.size() - 1) {
                    neighbors += state[i+1][j] == '#';
                }
                if (j > 0) {
                    neighbors += state[i][j-1] == '#';
                }
                if (j < state.size() - 1) {
                    neighbors += state[i][j+1] == '#';
                }


                if (neighbors == 1) {
                    new_state[i][j] = '#';
                } else if (neighbors == 2 && state[i][j] == '.') {
                    new_state[i][j] = '#';
                } else {
                    new_state[i][j] = '.';
                }
            }
        }
        state = new_state;
    }

    Answer ans = 0;
    for (uint32_t i = 0; i < state.size(); i++) {
        for (uint32_t j = 0; j < state.size(); j++) {
            if (state[i][j] == '#') {
                ans += 1 << (i * state.size() + j);
            }
        }
    }

    return ans;

}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {

    vector<string> zero_state = {
        ".....",
        ".....",
        "..?..",
        ".....",
        "....."
    };

    input[2][2] = '?';

    int minutes = 200;
    vector<vector<string>> states;
    for (int i = 0; i < minutes + 4; i++) {
        states.push_back(zero_state);
    }

    states[(minutes + 4) / 2] = input;

    for (int _ = 0; _ < minutes; _++) {
        vector<vector<string>> new_states = states;
        for (uint32_t s = 1; s < states.size() - 1; s++) {
            vector<string>& state = states[s];
            for (uint32_t i = 0; i < state.size(); i++) {
                for (uint32_t j = 0; j < state.size(); j++) {
                    if (i == 2 && j == 2) continue;
                    int neighbors = 0;
                    if (i == 0) {
                        neighbors += states[s+1][1][2] == '#';
                        neighbors += state[i+1][j] == '#';
                    } else if (i == 1 && j == 2) {
                        neighbors += state[i-1][j] == '#';
                        for (int k = 0; k < 5; k++) {
                            neighbors += states[s-1][0][k] == '#';
                        }
                    } else if (i == 3 && j == 2) {
                        neighbors += state[i+1][j] == '#';
                        for (int k = 0; k < 5; k++) {
                            neighbors += states[s-1][4][k] == '#';
                        }
                    } else if (i == 4) {
                        neighbors += states[s+1][3][2] == '#';
                        neighbors += state[i-1][j] == '#';
                    } else {
                        neighbors += state[i+1][j] == '#';
                        neighbors += state[i-1][j] == '#';
                    }

                    if (j == 0) {
                        neighbors += states[s+1][2][1] == '#';
                        neighbors += state[i][j+1] == '#';
                    } else if (j == 1 && i == 2) {
                        neighbors += state[i][j-1] == '#';
                        for (int k = 0; k < 5; k++) {
                            neighbors += states[s-1][k][0] == '#';
                        }
                    } else if (j == 3 && i == 2) {
                        neighbors += state[i][j+1] == '#';
                        for (int k = 0; k < 5; k++) {
                            neighbors += states[s-1][k][4] == '#';
                        }
                    } else if (j == 4) {
                        neighbors += states[s+1][2][3] == '#';
                        neighbors += state[i][j-1] == '#';
                    } else {
                        neighbors += state[i][j+1] == '#';
                        neighbors += state[i][j-1] == '#';
                    }

                    if (neighbors == 1) {
                        new_states[s][i][j] = '#';
                    } else if (neighbors == 2 && state[i][j] == '.') {
                        new_states[s][i][j] = '#';
                    } else {
                        new_states[s][i][j] = '.';
                    }
                }
            }
        }
        states = new_states;
    }

    Answer ans = 0;
    for (auto state : states) {
        for (uint32_t i = 0; i < state.size(); i++) {
            for (uint32_t j = 0; j < state.size(); j++) {
                ans += state[i][j] == '#';
            }
        }
    }

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
