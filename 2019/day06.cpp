#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;
using Input = unordered_map<int, int>;
using Answer = int;

int as_int(char a, char b, char c) {
    return a - '0' + 50 * (b - '0') + 2500 * (c - '0');
}

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    string temp;
    while (is >> temp) {
        input[as_int(temp[4], temp[5], temp[6])] = as_int(temp[0], temp[1], temp[2]);
    }
    is.close();

    return input;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 0;
    unordered_map<int, int> paths;
    paths.reserve(input.size());
    for (auto& orbit : input) {
        int planet = orbit.first;
        int length = 0;
        while (input.count(planet)) {
            if (paths.count(planet)) {
                length += paths[planet];
                break;
            }
            planet = input[planet];
            length++;
        }

        paths[orbit.first] = length;
        ans += length;
    }
    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = 0;
    unordered_map<int, int> path;
    int length = 0;
    int current = input[as_int('Y', 'O', 'U')];
    while (input.count(current)) {
        path[input[current]] = ++length;
        current = input[current];
    }

    length = 0;
    current = input[as_int('S', 'A', 'N')];
    while (!path.count(current)) {
        current = input[current];
        length++;
    }

    ans = path[current] + length;

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
