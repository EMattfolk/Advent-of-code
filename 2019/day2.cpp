#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include "collections.h"

using namespace std;
using Input = ArrayList<int>;
using Answer = int;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    int temp;
    while (is >> temp) {
        input.append(temp);
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

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input, int noun=12, int verb=2) {
    Answer ans = 0;
    Input program = input;
    program[1] = noun;
    program[2] = verb;
    for (unsigned int i = 0; i < program.len(); i += 4) {
        if (program[i] == 1) {
            add(program[program[i+1]], program[program[i+2]], program[program[i+3]]);
        } else if (program[i] == 2) {
            mul(program[program[i+1]], program[program[i+2]], program[program[i+3]]);
        } else if (program[i] == 99) {
            ans = program[0];
            break;
        } else {
            cout << "Error" << endl;
        }
    }
    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = 0;
    for (int noun = 0; noun < 100; noun++) {
        for (int verb = 0; verb < 100; verb++) {
            Input temp = input;
            if (solve_first(temp, noun, verb) == 19690720) {
                ans = 100 * noun + verb;
                break;
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
