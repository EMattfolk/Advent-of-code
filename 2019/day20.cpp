#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <cstdint>
#include <cctype>

using namespace std;
using Input = vector<string>;
using Answer = int;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    string temp;
    while (getline(is, temp)) {
        input.push_back(temp);
    }
    is.close();

    return input;
}

uint64_t pairhash(const pair<int, int>& pos) {
    const pair<int, int>* addr = &pos;
    return *((uint64_t*)addr);
}

uint64_t tdpairhash(const pair<int, pair<int, int>>& pos) {
    uint64_t h = pairhash(pos.second);
    return h + (pos.first << 16);
}

pair<int, int> pairunhash(const uint64_t& pos) {
    const uint64_t* addr = &pos;
    return *((pair<int, int>*)addr);
}

pair<int, int> rotate_dir(const pair<int, int>& dir) {
    return { -dir.second, dir.first };
}

int traverse(Input& input,
        unordered_map<string, vector<pair<int, int>>>& portals,
        pair<int, int> start,
        bool recurse=false)
{
    queue<pair<int, pair<int, int>>> to_visit;
    to_visit.push({ 0, start });

    unordered_set<uint64_t> visited;
    visited.insert(tdpairhash(to_visit.front()));

    int steps = 0;
    int next_step = 1;

    while (to_visit.size()) {

        pair<int, pair<int, int>> pos = to_visit.front();
        to_visit.pop();

        pair<int, int> dir = { 1, 0 };

        for (int i = 0; i < 4; i++) {
            pair<int, pair<int, int>> new_pos = { pos.first,
                { pos.second.first + dir.first, pos.second.second + dir.second }};
            int x = new_pos.second.first;
            int y = new_pos.second.second;

            if (visited.count(tdpairhash(new_pos)) || input[y][x] == '#') {
                dir = rotate_dir(dir);
                continue;
            }

            if (input[y][x] == '.') {
                visited.insert(tdpairhash(new_pos));
                to_visit.push(new_pos);
                dir = rotate_dir(dir);
                continue;
            }

            string name;
            name.push_back(input[y][x]);
            name.push_back(input[y + dir.second][x + dir.first]);
            if (name == "ZZ" && new_pos.first == 0) return steps;

            if (name == "AA" || name == "ZZ") {
                dir = rotate_dir(dir);
                continue;
            }


            if (i >= 2) {
                swap(name[0], name[1]);
            }

            if (pairhash(portals[name][0]) == pairhash(pos.second)) {
                new_pos.second = portals[name][1];
            } else {
                new_pos.second = portals[name][0];
            }

            if (recurse) {
                if (x == 1
                    || x == input[0].size() - 2
                    || y == 1
                    || y == input.size() - 2) {
                    if (new_pos.first == 0) {
                        dir = rotate_dir(dir);
                        continue;
                    } else {
                        new_pos.first--;
                    }
                } else {
                    new_pos.first++;
                }
            }

            if (!visited.count(tdpairhash(new_pos))) {
                visited.insert(tdpairhash(new_pos));
                to_visit.push(new_pos);
            }

            dir = rotate_dir(dir);
        }

        if (--next_step == 0) {
            steps++;
            next_step = to_visit.size();
        }
    }

    return -1;
}

unordered_map<string, vector<pair<int, int>>> portals;

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 0;
    for (uint32_t y = 0; y < input.size(); y++) {
        for (uint32_t x = 0; x < input[y].size() - 1; x++) {
            if (isupper(input[y][x]) && isupper(input[y][x+1])) {
                string name = "";
                name.push_back(input[y][x]);
                name.push_back(input[y][x+1]);
                if (x != 0 && input[y][x-1] == '.') {
                    portals[name].push_back({ x-1, y });
                } else {
                    portals[name].push_back({ x+2, y });
                }
            }
        }
    }
    for (uint32_t x = 0; x < input[0].size(); x++) {
        for (uint32_t y = 0; y < input.size() - 1; y++) {
            if (isupper(input[y][x]) && isupper(input[y+1][x])) {
                string name = "";
                name.push_back(input[y][x]);
                name.push_back(input[y+1][x]);
                if (y != 0 && input[y-1][x] == '.') {
                    portals[name].push_back({ x, y-1 });
                } else {
                    portals[name].push_back({ x, y+2 });
                }
            }
        }
    }

    pair<int, int> start = portals["AA"][0];
    portals["AA"].push_back(portals["ZZ"][0]);
    portals["ZZ"].push_back(portals["AA"][0]);

    ans = traverse(input, portals, start);

    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = traverse(input, portals, portals["AA"][0], true);
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
