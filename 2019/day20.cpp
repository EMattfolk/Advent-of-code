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

void rotate_dir(pair<int, int>& dir) {
    int temp = dir.first;
    dir.first = -dir.second;
    dir.second = temp;
}

int name_of(char a, char b) {
    return (a - 'A') * 26 + (b - 'A');
}

vector<pair<pair<int, int>, pair<int, int>>> portals(26*26, {{ 0, 0 }, { 0, 0 }});

int traverse(Input& input,
        pair<int, int> start,
        bool recurse=false)
{
    queue<pair<int, pair<int, int>>> to_visit;
    to_visit.push({ 0, start });

    vector<vector<vector<bool>>> visited;
    visited.push_back(vector<vector<bool>>());
    for (uint32_t i = 0; i < input.size(); i++) {
        visited[0].push_back(vector<bool>(input[i].size(), false));
    }
    visited[0][to_visit.front().second.second][to_visit.front().second.first] = true;

    int steps = 0;
    int next_step = 1;

    while (to_visit.size()) {

        pair<int, pair<int, int>> pos = to_visit.front();
        to_visit.pop();

        pair<int, int> dir = { 1, 0 };

        for (int i = 0; i < 4; i++) {
            pair<int, pair<int, int>> new_pos = { pos.first,
                { pos.second.first + dir.first, pos.second.second + dir.second }};
            int& depth = new_pos.first;
            int x = new_pos.second.first;
            int y = new_pos.second.second;

            if (input[y][x] == '#' || visited[depth][y][x]) {
                rotate_dir(dir);
                continue;
            }

            if (input[y][x] == '.') {
                visited[depth][y][x] = true;
                to_visit.push(new_pos);
                rotate_dir(dir);
                continue;
            }

            int name = name_of(input[y][x], input[y + dir.second][x + dir.first]);
            if (name == name_of('Z', 'Z') && new_pos.first == 0) return steps;

            if (name == name_of('A', 'A') || name == name_of('Z', 'Z')) {
                rotate_dir(dir);
                continue;
            }


            if (i >= 2) {
                name = name / 26 + 26 * (name % 26);
            }

            if (pairhash(portals[name].first) == pairhash(pos.second)) {
                new_pos.second = portals[name].second;
            } else {
                new_pos.second = portals[name].first;
            }

            if (recurse) {
                if (x == 1
                    || x == input[0].size() - 2
                    || y == 1
                    || y == input.size() - 2) {
                    if (new_pos.first == 0) {
                        rotate_dir(dir);
                        continue;
                    } else {
                        depth--;
                    }
                } else {
                    depth++;
                }
            }

            if (depth == visited.size()) {
                visited.push_back(vector<vector<bool>>());
                for (uint32_t i = 0; i < input.size(); i++) {
                    visited[depth].push_back(vector<bool>(input[i].size(), false));
                }
            }

            if (!visited[depth][new_pos.second.second][new_pos.second.first]) {
                visited[depth][new_pos.second.second][new_pos.second.first] = true;
                to_visit.push(new_pos);
            }

            rotate_dir(dir);
        }

        if (--next_step == 0) {
            steps++;
            next_step = to_visit.size();
        }
    }

    return -1;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 0;
    for (uint32_t y = 0; y < input.size(); y++) {
        for (uint32_t x = 0; x < input[y].size() - 1; x++) {
            if (isupper(input[y][x]) && isupper(input[y][x+1])) {
                int name = name_of(input[y][x], input[y][x+1]);
                pair<int, int>& opening =
                    (portals[name].first.first == 0 && portals[name].first.second == 0 ? portals[name].first : portals[name].second);
                if (x != 0 && input[y][x-1] == '.') {
                    opening = { x-1, y };
                } else {
                    opening = { x+2, y };
                }
            }
        }
    }
    for (uint32_t x = 0; x < input[0].size(); x++) {
        for (uint32_t y = 0; y < input.size() - 1; y++) {
            if (isupper(input[y][x]) && isupper(input[y+1][x])) {
                int name = name_of(input[y][x], input[y+1][x]);
                pair<int, int>& opening =
                    (portals[name].first.first == 0 && portals[name].first.second == 0 ? portals[name].first : portals[name].second);
                if (y != 0 && input[y-1][x] == '.') {
                    opening = { x, y-1 };
                } else {
                    opening = { x, y+2 };
                }
            }
        }
    }

    pair<int, int> start = portals[name_of('A', 'A')].first;
    portals[name_of('A', 'A')].second = portals[name_of('Z', 'Z')].first;
    portals[name_of('Z', 'Z')].second = portals[name_of('A', 'A')].first;

    ans = traverse(input, start);

    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = traverse(input, portals[name_of('A', 'A')].first, true);
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
