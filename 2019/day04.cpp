#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;
using Input = vector<int>;
using Answer = int;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    string temp;
    is >> temp;
    input.push_back(stoi(temp));
    input.push_back(stoi(temp.substr(7)));
    is.close();

    return input;
}

int digit(int n, int d) {
    return (n / (int)pow(10, 5 - d)) % 10;
}

//void get_matching(Input& input

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 0;
    int end = input.back();
    input.pop_back();
    int start = input.back();
    input.pop_back();
    for (int i = start; i <= end; i++) {
        bool doub = false;
        int digits[6];
        digits[0] = digit(i, 0);
        for (int d = 1; d < 6; d++) {
            digits[d] = digit(i, d);
            if (digits[d] < digits[d-1]) {
                doub = false;
                int p = (int)pow(10, 5-d);
                i -= i % (p * 10);
                i += digits[d-1] * p - 1;
                break;
            } else if (!doub) {
                for (int j = 0; j < d; j++) {
                    if (digits[j] == digits[d]) {
                        doub = true;
                        break;
                    }
                }
            }
        }

        if (doub) {
            ans++;
            int n = 0;
            int e = 1;
            for (int d = 5; d >= 0; d--) {
                n += e * digits[d];
                e *= 10;
            }
            input.push_back(n);
        }
    }
    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = 0;
    for (int n : input) {
        int digits[6];
        for (int d = 0; d < 6; d++) {
            digits[d] = digit(n, d);
        }
        bool valid = false;
        for (int d = 0; d < 10; d++) {
            int count = 0;
            for (int di : digits) {
                if (di == d) count++;
            }
            if (count == 2) {
                valid = true;
                break;
            }
        }
        if (valid) ans++;
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
