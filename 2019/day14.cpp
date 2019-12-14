#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstdint>

using namespace std;
using Input = unordered_map<string, vector<pair<int, string>>>;
using Answer = int64_t;

unordered_map<string, pair<int64_t, int64_t>> produce_table;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    string elem;
    int count;

    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);

    while (length - is.tellg() > 1) {
        vector<pair<int, string>> req;
        bool req_done = false;
        while (!req_done) {
            is >> count;
            is >> elem;
            if (elem[elem.size()-1] == ',') {
                req.push_back({ count, elem.substr(0, elem.size()-1) });
            } else {
                req.push_back({ count, elem });
                req_done = true;
            }
        }
        is >> elem;
        is >> count;
        is >> elem;
        input[elem] = req;
        produce_table[elem] = { count, 0 };
    }
    is.close();

    return input;
}

int64_t produce_element(Input& input, int64_t count, string elem) {
    int64_t to_produce = count - produce_table[elem].second;
    int64_t cycles = 0;
    if (to_produce > 0) {
        cycles += to_produce / produce_table[elem].first;
        to_produce -= cycles * produce_table[elem].first;
        if (to_produce > 0) {
            to_produce -= produce_table[elem].first;
            cycles++;
        }
    }

    to_produce = produce_table[elem].first * cycles;

    int64_t ores = 0;
    if (to_produce) {
        for (pair<int, string>& ingredient : input[elem]) {
            //cout << ingredient.second << endl;
            int64_t amount = cycles * ingredient.first;
            //cout << amount << endl;
            if (ingredient.second == "ORE") {
                ores += amount;
            } else {
                ores += produce_element(input, amount, ingredient.second);
                produce_table[ingredient.second].second -= amount;
            }
        }
    }


    produce_table[elem].second += to_produce;

    return ores;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input, int64_t fuel=1) {
    auto ptable = produce_table;
    Answer ans = produce_element(input, fuel, "FUEL");
    produce_table = ptable;
    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    int64_t lower = 0;
    int64_t upper = 1000000000000;
    while (lower != upper && lower + 1 != upper) {
        int64_t err = 1000000000000 - solve_first(input, (lower + upper) / 2);
        if (err < 0) {
            upper = (upper + lower) / 2;
        } else {
            lower = (upper + lower) / 2;
        }
    }

    Answer ans;
    if (solve_first(input, upper) > 1000000000000) {
        ans = lower;
    } else {
        ans = upper;
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
