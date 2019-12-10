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

Answer run_program(Input& input, int64_t write) {
    Answer res = 0;
    Input& program = input;
    relative_base = 0;
    uint64_t i = 0;
    while (true) {
        int64_t opcode = program[i] % 100;
        if (opcode == 99) {
            break;
        }

        int64_t mode1 = (program[i] / 100) % 10;
        int64_t& arg1 = get_value(program, mode1, program[i+1]);
        if (opcode == 3) {
            arg1 = write;
            i += 2;
            continue;
        } else if (opcode == 4) {
            res = arg1;
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

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    return run_program(input, 1);
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    return run_program(input, 2);
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
