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

    return input;
}

unordered_map<uint64_t, int64_t> memory;
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
    if (mode == 0) {
        if ((uint64_t)value >= program.size())
            return memory[value];
        return program[value];
    }
    else if (mode == 1) return value;
    else {
        if (value + relative_base >= program.size())
            return memory[relative_base + value];
        return program[relative_base + value];
    }
}

Answer run_program(Input& input, int64_t write) {
    Answer res = 0;
    Input& program = input;
    vector<int64_t> fn_values;
    memory.clear();
    relative_base = 0;
    uint64_t i = 0;
    while (true) {
        int64_t opcode = program[i] % 100;
        int64_t mode = (program[i] / 100) % 10;
        if (opcode == 99) {
            break;
        }

        int64_t& val = get_value(program, mode, program[i+1]);
        if (opcode == 3) {
            val = write;
            i += 2;
            continue;
        }
        if (opcode == 4) {
            return val;
        } else if (opcode == 9) {
            relative_base += val;
            i += 2;
            continue;
        }

        fn_values.push_back(get_value(program, mode, program[i+1]));
        mode = (program[i] / 1000) % 10;
        fn_values.push_back(get_value(program, mode, program[i+2]));

        mode = (program[i] / 10000) % 10;
        if (opcode == 1) {
            uint64_t addr;
            if (mode == 0) {
                addr = program[i+3];
            } else if (mode == 2) {
                addr = relative_base + program[i+3];
            }
            if (addr >= program.size())
                add(fn_values[0], fn_values[1], memory[addr]);
            else
                add(fn_values[0], fn_values[1], program[addr]);
        } else if (opcode == 2) {
            uint64_t addr;
            if (mode == 0) {
                addr = program[i+3];
            } else if (mode == 2) {
                addr = relative_base + program[i+3];
            }
            if (addr >= program.size())
                mul(fn_values[0], fn_values[1], memory[addr]);
            else
                mul(fn_values[0], fn_values[1], program[addr]);
        } else if (opcode == 5) {
            i += 3;
            jit(i, fn_values[0], fn_values[1]);
            fn_values.clear();
            continue;
        } else if (opcode == 6) {
            i += 3;
            jif(i, fn_values[0], fn_values[1]);
            fn_values.clear();
            continue;
        } else if (opcode == 7) {
            uint64_t addr;
            if (mode == 0) {
                addr = program[i+3];
            } else if (mode == 2) {
                addr = relative_base + program[i+3];
            }
            if (addr >= program.size())
                les(fn_values[0], fn_values[1], memory[addr]);
            else
                les(fn_values[0], fn_values[1], program[addr]);
        } else if (opcode == 8) {
            uint64_t addr;
            if (mode == 0) {
                addr = program[i+3];
            } else if (mode == 2) {
                addr = relative_base + program[i+3];
            }
            if (addr >= program.size())
                equ(fn_values[0], fn_values[1], memory[addr]);
            else
                equ(fn_values[0], fn_values[1], program[addr]);
        } else {
            cout << "Error: opcode = " << opcode << endl;
        }
        fn_values.clear();
        i += 4;
    }
    return res;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    return run_program(input,1);
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    return run_program(input,2);
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
