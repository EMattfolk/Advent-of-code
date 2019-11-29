#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include "collections.h"

using namespace std;
using Input = string;
using Answer = int;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    is >> input;
    is.close();

    return input;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 0;
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] == input[(i+1) % input.size()])
            ans += input[i] - '0';
    }
    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = 0;
    size_t step = input.size() / 2;
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] == input[(i+step) % input.size()])
            ans += input[i] - '0';
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

    cout << "First: " << first_answer << endl
        << "Second: " << second_answer << endl
        << "Time: " << chrono::duration_cast<chrono::milliseconds>(end-start).count()
        << "ms" << endl;

    return 0;
}
