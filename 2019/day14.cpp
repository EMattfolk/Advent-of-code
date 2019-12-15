#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <cstdint>

using namespace std;
using Input = vector<vector<pair<int, int>>>;
using Answer = int64_t;

// [(amount produced in one cycle, current amount), ..]
vector<pair<int64_t, int64_t>> produce_table;

int FUEL = 0;
int ORE = 0;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    string elem;
    int count;

    unordered_map<string, int> translation;

    auto add_translation = [&translation, &input](string& elem) {
        translation[elem] = input.size();
        input.push_back(vector<pair<int, int>>());
        produce_table.push_back({ 0, 0 });
    };

    while (is >> ws && !is.eof()) {
        vector<pair<int, int>> req;
        bool req_done = false;
        while (!req_done) {
            is >> count;
            is >> elem;
            if (elem[elem.size()-1] == ',') {
                elem = elem.substr(0, elem.size()-1);
            } else {
                req_done = true;
            }

            if (translation.count(elem) == 0) add_translation(elem);
            req.push_back({ count, translation[elem] });
        }

        is >> elem;
        is >> count;
        is >> elem;

        if (translation.count(elem) == 0) add_translation(elem);
        input[translation[elem]] = req;
        produce_table[translation[elem]] = { count, 0 };
    }

    is.close();

    FUEL = translation["FUEL"];
    ORE = translation["ORE"];

    return input;
}

int64_t produce_element(Input& input, int64_t count, int elem) {
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
        for (pair<int, int>& ingredient : input[elem]) {
            int64_t amount = cycles * ingredient.first;
            if (ingredient.second == ORE) {
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
Answer solve_first(Input& input, int64_t count=1) {
    Answer ans = produce_element(input, count, FUEL);

    for (pair<int64_t, int64_t>& p : produce_table) {
        p.second = 0;
    }

    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    int64_t lower = 0;
    int64_t upper = 2000000000000 / solve_first(input, 1);
    while (lower + 1 != upper) {
        int64_t err = 1000000000000 - solve_first(input, (lower + upper) / 2);
        if (err < 0) {
            upper = (upper + lower) / 2;
        } else {
            lower = (upper + lower) / 2;
        }
    }

    return lower;
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
