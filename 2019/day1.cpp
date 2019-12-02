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
    while(is >> temp) {
        input.append(temp);
    }
    is.close();

    return input;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 0;
    for (auto it = input.iter(); it.valid(); it.next()) {
        ans += *it / 3 - 2;
    }
    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = 0;
    for (auto it = input.iter(); it.valid(); it.next()) {
        while ((*it = *it / 3 - 2) >= 0) {
            ans += *it;
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
