#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;
using Input = vector<int64_t>;
using Answer = string;

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

    while (input.size() < 6000) input.push_back(0);

    return input;
}

class IntCode {
public:

    IntCode(vector<int64_t>& program) : program(program) {}

    void run_one() {

        int64_t opcode = program[program_index] % 100;
        if (opcode == 99) {
            halted = true;
            return;
        }

        int64_t mode1 = (program[program_index] / 100) % 10;
        int64_t& arg1 = get_value(program, mode1, program[program_index+1]);
        if (opcode == 3) {
            if (in.size()) {
                arg1 = in.front();
                in.pop();
                idle = false;
            } else {
                idle = true;
                return;
            }
            program_index += 2;
            return;
        } else if (opcode == 4) {
            out.push(arg1);
            program_index += 2;
            return;
        } else if (opcode == 9) {
            relative_base += arg1;
            program_index += 2;
            return;
        }

        int64_t mode2 = (program[program_index] / 1000) % 10;
        int64_t& arg2 = get_value(program, mode2, program[program_index+2]);
        if (opcode == 5) {
            program_index += 3;
            jit(program_index, arg1, arg2);
            return;
        } else if (opcode == 6) {
            program_index += 3;
            jif(program_index, arg1, arg2);
            return;
        }

        uint64_t mode3 = (program[program_index] / 10000) % 10;
        int64_t& arg3 = get_value(program, mode3, program[program_index+3]);
        if (opcode == 1) {
            add(arg1, arg2, arg3);
        } else if (opcode == 2) {
            mul(arg1, arg2, arg3);
        } else if (opcode == 7) {
            les(arg1, arg2, arg3);
        } else if (opcode == 8) {
            equ(arg1, arg2, arg3);
        }
        program_index += 4;
    }

    int64_t& get_value(Input& program, int64_t mode, int64_t& value) {
        if (mode == 0) return program[value];
        else if (mode == 1) return value;
        else return program[relative_base + value];
    }

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

    vector<int64_t> program;
    queue<int64_t> out;
    queue<int64_t> in;
    bool halted = false;
    bool idle = false;
    uint64_t relative_base = 0;
    uint64_t program_index = 0;
};

void give_input(IntCode& program, string data) {
    for (char c : data) {
        program.in.push(c);
    }
    program.in.push(10);
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    IntCode program(input);

    give_input(program, "south");
    give_input(program, "take mutex");
    give_input(program, "south");
    give_input(program, "east");
    give_input(program, "west");
    give_input(program, "west");
    give_input(program, "west");
    give_input(program, "take klein bottle");
    give_input(program, "east");
    give_input(program, "east");
    give_input(program, "north");
    give_input(program, "east");
    give_input(program, "take mug");
    give_input(program, "east");
    give_input(program, "north");
    give_input(program, "north");
    give_input(program, "take hypercube");
    give_input(program, "south");
    give_input(program, "south");
    give_input(program, "east");
    give_input(program, "east");
    give_input(program, "east");
    give_input(program, "south");
    give_input(program, "west");
    give_input(program, "west");

    while (!program.halted) {
        program.run_one();
    }

    string ans;
    bool at_santa = false;
    while (program.out.size()) {
        char letter = program.out.front();
        program.out.pop();

        if (at_santa && letter >= '0' && letter <= '9') {
            ans.push_back(letter);
        }

        at_santa |= letter == '"';
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

    auto end = chrono::high_resolution_clock::now();

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();

    cout << first_answer << " - " << elapsed << "ms" << endl;

    return 0;
}
