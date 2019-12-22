#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

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

    while (input.size() < 4000) input.push_back(0);

    return input;
}

class IntCode {
public:

    IntCode(vector<int64_t>& program) : program(program) {}

    int64_t run(string& input) {
        int64_t res = 0;
        while (true) {
            int64_t opcode = program[program_index] % 100;
            if (opcode == 99) {
                halted = true;
                return -1;
            }

            int64_t mode1 = (program[program_index] / 100) % 10;
            int64_t& arg1 = get_value(program, mode1, program[program_index+1]);
            if (opcode == 3) {
                arg1 = input[input_index++];
                program_index += 2;
                continue;
            } else if (opcode == 4) {
                res = arg1;
                program_index += 2;
                break;
            } else if (opcode == 9) {
                relative_base += arg1;
                program_index += 2;
                continue;
            }

            int64_t mode2 = (program[program_index] / 1000) % 10;
            int64_t& arg2 = get_value(program, mode2, program[program_index+2]);
            if (opcode == 5) {
                program_index += 3;
                jit(program_index, arg1, arg2);
                continue;
            } else if (opcode == 6) {
                program_index += 3;
                jif(program_index, arg1, arg2);
                continue;
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
        return res;
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
    bool halted = false;
    uint64_t relative_base = 0;
    uint64_t program_index = 0;
    uint32_t input_index = 0;
};

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    IntCode program(input);
    string instr;
    instr += "NOT A J\n";
    instr += "NOT C T\n";
    instr += "AND D T\n";
    instr += "OR T J\n";
    instr += "WALK\n";

    Answer ans;
    while (true) {
        int64_t res = program.run(instr);
        if (res > 256) {
            ans = res;
            break;
        }
#ifdef OUTPUT
        cout << (char)res;
        cout.flush();
#endif
    }

    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    IntCode program(input);
    string instr;

    // Three ahead
    instr += "NOT C T\n";
    instr += "AND D T\n";
    instr += "NOT H J\n";
    instr += "NOT J J\n";
    instr += "OR E J\n";
    instr += "AND T J\n";

    // Jump if next is hole
    instr += "NOT A T\n";
    instr += "OR T J\n";

    // Jump if waiting results in death
    instr += "NOT B T\n";
    instr += "AND A T\n";
    instr += "AND D T\n";
    instr += "OR T J\n";

    // GO
    instr += "RUN\n";

    Answer ans = 0;
    while (!program.halted) {
        int64_t res = program.run(instr);
        if (res > 256) {
            ans = res;
            break;
        }
#ifdef OUTPUT
        cout << (char)res;
        cout.flush();
#endif
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
