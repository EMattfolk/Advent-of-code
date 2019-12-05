#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
using Input = vector<int>;
using Answer = int;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    int temp;
    while (is >> temp) {
        input.push_back(temp);
        is.ignore(1);
    }
    is.close();

    return input;
}

void add(vector<int>& values, int& c) {
    c = 0;
    for (int v : values) {
        c += v;
    }
}

void mul(vector<int>& values, int& c) {
    c = 1;
    for (int v : values) {
        c *= v;
    }
}

void jit(unsigned int& instr, int a, int b) {
    if (a) instr = b;
}

void jif(unsigned int& instr, int a, int b) {
    if (!a) instr = b;
}

void les(int a, int b, int& c) {
    c = a < b;
}

void equ(int a, int b, int& c) {
    c = a == b;
}

int get_value(Input& program, int mode, int value) {
    if (mode == 0) return program[value];
    else if (mode == 1) return value;
    else { cout << "Error at get_value" << endl; }
    return -1;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 0;
    Input program = input;
    vector<int> fn_values;
    unsigned int i = 0;
    while (i < program.size()) {
        int opcode = program[i] % 100;
        if (opcode == 3) {
            program[program[i+1]] = 1;
            i += 2;
            continue;
        }
        int val = get_value(program, program[i] / 100 % 10, program[i+1]);
        if (opcode == 4) {
            if (val) {
                ans = val;
                break;
            }
            i += 2;
            continue;
        }
        int pos = 1;
        int div = 100;
        while (pos <= 2 || program[i] / div) {
            int mode = (program[i] / div) % 10;
            fn_values.push_back(get_value(program, mode, program[i+pos]));
            div *= 10;
            pos++;
        }
        if (opcode == 1) {
            add(fn_values, program[program[i+pos]]);
        } else if (opcode == 2) {
            mul(fn_values, program[program[i+pos]]);
        } else if (opcode == 99) {
            ans = program[0];
            break;
        } else {
            cout << "Error: opcode = " << opcode << endl;
        }
        //cout << program[i] << endl;
        fn_values.clear();
        i += pos+1;
    }
    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = 0;
    Input program = input;
    vector<int> fn_values;
    unsigned int i = 0;
    while (i < program.size()) {
        int opcode = program[i] % 100;
        if (opcode == 3) {
            program[program[i+1]] = 5;
            i += 2;
            continue;
        }
        int val = get_value(program, program[i] / 100 % 10, program[i+1]);
        if (opcode == 4) {
            if (val) {
                ans = val;
                break;
            }
            i += 2;
            continue;
        }
        int pos = 1;
        int div = 100;
        while (pos <= 2 || program[i] / div) {
            int mode = (program[i] / div) % 10;
            fn_values.push_back(get_value(program, mode, program[i+pos]));
            div *= 10;
            pos++;
        }
        if (opcode == 1) {
            add(fn_values, program[program[i+pos]]);
        } else if (opcode == 2) {
            mul(fn_values, program[program[i+pos]]);
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
            les(fn_values[0], fn_values[1], program[program[i+pos]]);
        } else if (opcode == 8) {
            equ(fn_values[0], fn_values[1], program[program[i+pos]]);
        } else if (opcode == 99) {
            ans = program[0];
            break;
        } else {
            cout << "Error: opcode = " << opcode << endl;
        }
        //cout << program[i] << endl;
        fn_values.clear();
        i += pos+1;
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
