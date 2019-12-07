#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

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

void add(int a, int b, int& c) {
    c = a + b;
}

void mul(int a, int b, int& c) {
    c = a * b;
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

Answer run_program(Input& input, vector<int>& setting, unsigned int* index=nullptr, bool* halted=nullptr) {
    Answer res = 0;
    Input& program = input;
    vector<int> fn_values;
    int setting_index = 0;
    unsigned int i = (index ? *index : 0);
    while (i < program.size()) {
        int opcode = program[i] % 100;
        if (opcode == 3) {
            program[program[i+1]] = setting[setting_index++];
            i += 2;
            continue;
        } else if (opcode == 99) {
            if (halted) *halted = true;
            res = setting[1];
            break;
        }
        int val = get_value(program, program[i] / 100 % 10, program[i+1]);
        if (opcode == 4) {
            res = val;
            i += 2;
            if (index) *index = i;
            break;
        }

        int mode = (program[i] / 100) % 10;
        fn_values.push_back(get_value(program, mode, program[i+1]));
        mode = (program[i] / 1000) % 10;
        fn_values.push_back(get_value(program, mode, program[i+2]));

        if (opcode == 1) {
            add(fn_values[0], fn_values[1], program[program[i+3]]);
        } else if (opcode == 2) {
            mul(fn_values[0], fn_values[1], program[program[i+3]]);
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
            les(fn_values[0], fn_values[1], program[program[i+3]]);
        } else if (opcode == 8) {
            equ(fn_values[0], fn_values[1], program[program[i+3]]);
        } else {
            cout << "Error: opcode = " << opcode << endl;
        }
        fn_values.clear();
        i += 4;
    }
    return res;
}

bool ispermutation(vector<int>& perm) {
    for (unsigned int i = 0; i < perm.size(); i++) {
        for (unsigned int j = i+1; j < perm.size(); j++) {
            if (perm[i] == perm[j]) return false;
        }
    }
    return true;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 0;
    vector<int> setting;
    vector<int> permutation = { 0, 1, 2, 3, 4 };
    do {
        Answer res = 0;
        for (int p : permutation) {
            setting.push_back(p);
            setting.push_back(res);
            Input program(input);
            res = run_program(program, setting, nullptr, nullptr);
            setting.pop_back();
            setting.pop_back();
        }
        if (res > ans) ans = res;
    } while (next_permutation(permutation.begin(), permutation.end()));

    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = 0;
    vector<int> setting;
    vector<int> permutation = { 5, 6, 7, 8, 9 };
    do {
        unsigned int indexes[5] = { 0, 0, 0, 0, 0 };
        Input amps[5] = { input, input, input, input, input };
        Answer res = 0;
        bool halted = false;
        for (unsigned int p = 0; p < permutation.size(); p++) {
            setting.push_back(permutation[p]);
            setting.push_back(res);
            res = run_program(amps[p], setting, indexes+p, &halted);
            setting.clear();
        }
        while (!halted) {
            for (unsigned int p = 0; p < permutation.size(); p++) {
                setting.push_back(res);
                res = run_program(amps[p], setting, indexes+p, &halted);
                setting.clear();
            }
            if (res > ans) ans = res;
        }
    } while (next_permutation(permutation.begin(), permutation.end()));

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
