#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdint>

using namespace std;
using Input = vector<uint8_t>;
using Answer = int;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    string temp;
    ifstream is(filename);
    is >> temp;
    is.close();

    for (char c : temp) input.push_back(c - '0');

    return input;
}

int8_t s[4] = { 0, 1, 0, -1 };
int8_t series(int p, int i) {
    return s[(i / p) & 3];
}

int first_n(vector<uint8_t>& nums, int n) {
    int res = 0;
    int place = 1;
    for (int i = n-1; i >= 0; i--) {
        res += nums[i] * place;
        place *= 10;
    }

    return res;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    vector<uint8_t> data = input;
    for (uint8_t i = 0; i < 100; i++) {
        for (uint32_t j = 0; j < data.size() / 2; j++) {
            int32_t value = 0;
            int8_t mult = -1;
            for (uint32_t block = j; block < data.size(); block += j*2 + 2) {
                mult *= -1;
                for (uint32_t k = block; k < block + j + 1 && k < data.size(); k++) {
                    value += data[k] * mult;
                }
            }
            data[j] = abs(value) % 10;
        }
        int32_t cum_sum = 0;
        for (uint32_t j = data.size() / 2; j < data.size(); j++) cum_sum += data[j];
        for (uint32_t j = data.size() / 2; j < data.size(); j++) {
            uint8_t temp = data[j];
            data[j] = cum_sum % 10;
            cum_sum -= temp;
        }
    }
    return first_n(data, 8);
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    uint32_t offset = first_n(input, 7);
    uint32_t end = input.size() * 10000;
    vector<uint8_t> data;
    data.reserve(end - offset + 1);
    for (uint32_t i = offset; i < end; i++) {
        data.push_back(input[i % input.size()]);
    }

    for (int phase = 0; phase < 100; phase++) {
        int32_t cum_sum = 0;
        for (uint8_t c : data) cum_sum += c;
        for (uint32_t i = 0; i < data.size(); i++) {
            int temp = data[i];
            data[i] = cum_sum % 10;
            cum_sum -= temp;
        }
    }

    return first_n(data, 8);
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
