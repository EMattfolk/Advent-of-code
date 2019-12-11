#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

//#define OUTPUT

using namespace std;
using Input = vector<int64_t>;
using Answer = int64_t;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    int64_t temp;
    while (is >> temp) {
        input.push_back(temp);
        is.ignore(1);
    }
    is.close();

    while (input.size() < 2000) input.push_back(0);

    return input;
}

uint64_t relative_base = 0;

void add(int64_t a, int64_t b, int64_t& c) {
    c = a + b;
}

void mul(int64_t a, int64_t b, int64_t& c) {
    c = a * b;
}

void jit(uint64_t& instr, int64_t a, int64_t b) {
    if (a) instr = b;
}

void jif(uint64_t& instr, int64_t a, int64_t b) {
    if (!a) instr = b;
}

void les(int64_t a, int64_t b, int64_t& c) {
    c = a < b;
}

void equ(int64_t a, int64_t b, int64_t& c) {
    c = a == b;
}

int64_t& get_value(Input& program, int64_t mode, int64_t& value) {
    if (mode == 0) return program[value];
    else if (mode == 1) return value;
    else return program[relative_base + value];
}

Answer run_program(Input& program, uint64_t& i, int64_t write) {
    Answer res = 0;
    while (true) {
        int64_t opcode = program[i] % 100;
        if (opcode == 99) {
            return -1;
        }

        int64_t mode1 = (program[i] / 100) % 10;
        int64_t& arg1 = get_value(program, mode1, program[i+1]);
        if (opcode == 3) {
            arg1 = write;
            i += 2;
            continue;
        } else if (opcode == 4) {
            res = arg1;
            i += 2;
            break;
        } else if (opcode == 9) {
            relative_base += arg1;
            i += 2;
            continue;
        }

        int64_t mode2 = (program[i] / 1000) % 10;
        int64_t& arg2 = get_value(program, mode2, program[i+2]);
        if (opcode == 5) {
            i += 3;
            jit(i, arg1, arg2);
            continue;
        } else if (opcode == 6) {
            i += 3;
            jif(i, arg1, arg2);
            continue;
        }

        uint64_t mode3 = (program[i] / 10000) % 10;
        int64_t& arg3 = get_value(program, mode3, program[i+3]);
        if (opcode == 1) {
            add(arg1, arg2, arg3);
        } else if (opcode == 2) {
            mul(arg1, arg2, arg3);
        } else if (opcode == 7) {
            les(arg1, arg2, arg3);
        } else if (opcode == 8) {
            equ(arg1, arg2, arg3);
        }
        i += 4;
    }
    return res;
}

uint64_t pairhash(const pair<int, int>& pos) {
    const pair<int, int>* addr = &pos;
    return *((uint64_t*)addr);
}

pair<int, int> pairunhash(const uint64_t& pos) {
    const uint64_t* addr = &pos;
    return *((pair<int, int>*)addr);
}

unordered_map<uint64_t, int> paint_hull(Input& input, int start) {
    Input program = input;
    relative_base = 0;
    unordered_map<uint64_t, int> colors;
    pair<int, int> pos = { 0, 0 };
    pair<int, int> dir = { 0, 1 };
    colors[pairhash(pos)] = start;
    uint64_t index = 0;
    while (true) {
        int color = run_program(program, index, colors[pairhash(pos)]);
        if (color == -1) break;
        int turn = run_program(program, index, colors[pairhash(pos)]);
        colors[pairhash(pos)] = color;
        if (turn == 0) {
            dir = { -dir.second, dir.first };
        } else {
            dir = { -dir.second, dir.first };
            dir = { -dir.second, dir.first };
            dir = { -dir.second, dir.first };
        }
        pos.first += dir.first;
        pos.second += dir.second;
    }

    return colors;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Input program = input;
    return paint_hull(program, 0).size();
}

/*
 * Solve the second problem.
 */
string solve_second(Input& input) {
    Input program = input;
    auto colors = paint_hull(program, 1);

#ifdef OUTPUT

    int min_x = 1 << 30;
    int max_x = 1 << 31;
    int min_y = 1 << 30;
    int max_y = 1 << 31;
    for (pair<uint64_t, int> elem : colors) {
        pair<int, int> pos = pairunhash(elem.first);
        if (pos.first < min_x) min_x = pos.first;
        if (pos.first > max_x) max_x = pos.first;
        if (pos.second < min_y) min_y = pos.second;
        if (pos.second > max_y) max_y = pos.second;
    }

    int width = max_x - min_x + 1;
    int height = max_y - min_y + 1;
    char** grid = new char*[height];
    for (int i = 0; i < height; i++) {
        grid[i] = new char[width+1];
        for (int j = 0; j < width; j++) {
            grid[i][j] = ' ';
        }
        grid[i][width] = '\0';
    }

    cout << endl;
    for (pair<uint64_t, int> elem : colors) {
        pair<int, int> pos = pairunhash(elem.first);
        if (elem.second == 1) {
            grid[pos.second - min_y][pos.first - min_x] = '#';
        }
    }

    for (int i = height - 1; i >= 0; i--) {
        cout << grid[i] << endl;
    }

#endif

    return "KRZEAJHB";
}

/*
 * Run solutions.
 */
int main(int argc, char** argv) {

    Input input = get_input(argv[1]);

    auto start = chrono::high_resolution_clock::now();

    Answer first_answer = solve_first(input);
    string second_answer = solve_second(input);

    auto end = chrono::high_resolution_clock::now();

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();

    cout << first_answer << ", " << second_answer << " - " << elapsed << "ms" << endl;

    return 0;
}
