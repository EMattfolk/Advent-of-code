#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

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

    while (input.size() < 4000) input.push_back(0);

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

Answer run_program(Input& program, uint64_t& i, int64_t write, bool* halted=nullptr) {
    Answer res = 0;
    while (true) {
        int64_t opcode = program[i] % 100;
        if (opcode == 99) {
            if (halted) *halted = true;
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

//uint64_t pairhash(const pair<int, int>& pos) {
//    const pair<int, int>* addr = &pos;
//    return *((uint64_t*)addr);
//}
//
//pair<int, int> pairunhash(const uint64_t& pos) {
//    const uint64_t* addr = &pos;
//    return *((pair<int, int>*)addr);
//}

Answer count_tiles(Input& program) {
    int count = 0;
    relative_base = 0;
    bool halted = false;
    uint64_t index = 0;
    while (true) {
        run_program(program, index, 0, &halted);
        if (halted) break;
        run_program(program, index, 0);
        int color = run_program(program, index, 0);
        if (color == 2) {
            count++;
        }
    }

    return count;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Input program = input;
    return count_tiles(program);
}

//void printgrid(char** grid) {
//    for (int i = 0; i < 24; i++) {
//        cout << grid[i] << endl;
//    }
//}
//
//void render(unordered_map<uint64_t, int>& board, char** grid) {
//    for (auto e : board) {
//        pair<int, int> pos = pairunhash(e.first);
//        char c;
//        if (e.second == 0) {
//            c = ' ';
//        } else if (e.second == 1) {
//            c = '#';
//        } else if (e.second == 2) {
//            c = 'T';
//        } else if (e.second == 3) {
//            c = '_';
//        } else if (e.second == 4) {
//            c = 'O';
//        }
//
//        grid[pos.second][pos.first] = c;
//    }
//}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    //char** grid = new char*[24];
    //for (int i = 0; i < 24; i++) {
    //    grid[i] = new char[43];
    //    for (int j = 0; j < 43; j++) {
    //        grid[i][j] = ' ';
    //    }
    //    grid[i][42] = '\0';
    //}

    input[0] = 2;
    relative_base = 0;
    //unordered_map<uint64_t, int> board;

    Answer ans = 0;
    bool halted = false;
    uint64_t index = 0;

    int joystick = 0;
    int paddle = 0;
    int ball = 0;

    while (!halted) {
        int x = run_program(input, index, joystick, &halted);
        if (halted) break;
        int y = run_program(input, index, joystick);
        int tile = run_program(input, index, joystick);

        if (tile == 3) paddle = x;
        else if (tile == 4) ball = x;

        if (paddle < ball) joystick = 1;
        else if (paddle == ball) joystick = 0;
        else if (paddle > ball) joystick = -1;

        //pair<int, int> pos = { x, y };
        if (x == -1 && y == 0) {
            ans = tile;
            //cout << tile << endl;
            //continue;
        }
        //board[pairhash(pos)] = tile;
        //render(board, grid);
        //printgrid(grid);
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
