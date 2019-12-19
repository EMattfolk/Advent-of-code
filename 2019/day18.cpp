#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cstdint>
#include <cctype>

using namespace std;
using Input = vector<string>;
using Answer = int;

pair<int, int> start = { 0, 0 };

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

    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[y].size(); x++) {
            if (input[y][x] == '@') {
                input[y][x] = '.';
                start = { x, y };
                break;
            }
        }
    }

    return input;
}

uint64_t pairhash(const pair<int, int>& pos) {
    const pair<int, int>* addr = &pos;
    return *((uint64_t*)addr);
}

pair<int, int> pairunhash(const uint64_t& pos) {
    const uint64_t* addr = &pos;
    return *((pair<int, int>*)addr);
}

pair<int, int> rotate_dir(const pair<int, int>& dir) {
    return { -dir.second, dir.first };
}

vector<string> get_dependencies(
        vector<string>& grid,
        unordered_set<uint64_t>& visited,
        pair<int, int> pos)
{
    visited.insert(pairhash(pos));

    // Dependency at this position
    string dep_at_pos = "";
    if (grid[pos.second][pos.first] != '.') {
        dep_at_pos += grid[pos.second][pos.first];
    }

    vector<string> dependencies;
    pair<int, int> dir = { 1, 0 };

    for (int i = 0; i < 4; i++) {

        // New position
        pair<int, int> new_pos = { pos.first + dir.first, pos.second + dir.second };
        dir = rotate_dir(dir);

        // Avoid places we don't want to go to
        if (visited.count(pairhash(new_pos)) ||
                grid[new_pos.second][new_pos.first] == '#') continue;

        // Create dependencies from other dependencies
        for (string dep : get_dependencies(grid, visited, new_pos)) {
            dependencies.push_back(dep_at_pos + dep);
        }
    }

    // Base case
    if (dependencies.empty() && !dep_at_pos.empty()) {
        dependencies.push_back(dep_at_pos);
    }

    return dependencies;
}

void clean_dependencies(vector<string>& dependencies) {
    for (int i = dependencies.size() - 1; i >= 0; i--) {

        int to_keep = 0;
        for (int j = dependencies[i].size() - 1; j >= 0; j--) {
            if (islower(dependencies[i][j])) {
                to_keep = j + 1;
                break;
            }
        }

        if (to_keep == 0) {
            dependencies.erase(dependencies.begin() + i);
        } else {
            dependencies[i] = dependencies[i].substr(0, to_keep);
        }
    }
}

void unlock_key(vector<string>& dependencies, char key) {
    for (int i = 0; i < dependencies.size(); i++) {
        for (int j = dependencies[i].size() - 1; j >= 0; j--) {
            if (dependencies[i][j] == key || dependencies[i][j] == toupper(key)) {
                dependencies[i].erase(dependencies[i].begin() + j);
            }
        }
    }

    clean_dependencies(dependencies);
}

vector<char> current_dependencies(vector<string>& dependencies) {
    unordered_set<char> visible;
    unordered_set<char> found;
    vector<char> deps;
    for (string& dependency : dependencies) {
        for (char dep : dependency) {
            if (isupper(dep)) break;
            visible.insert(dep);
        }
    }
    for (string& dependency : dependencies) {
        for (char dep : dependency) {
            if (isupper(dep)) {
                char l = tolower(dep);
                if (visible.count(l) && found.count(l) == 0) {
                    deps.push_back(l);
                    found.insert(l);
                }
                break;
            }
        }
    }

    return deps;
}

// Returns a path to a key with ends inclusive. size()-1 steps.
vector<pair<int, int>> path_to(
        vector<string>& grid,
        unordered_set<uint64_t>& visited,
        pair<int, int> pos,
        char key)
{
    visited.insert(pairhash(pos));

    // Done?
    if (grid[pos.second][pos.first] == key) {
        return { pos };
    }

    pair<int, int> dir = { 1, 0 };

    for (int i = 0; i < 4; i++) {

        // New position
        pair<int, int> new_pos = { pos.first + dir.first, pos.second + dir.second };
        dir = rotate_dir(dir);

        // Avoid places we don't want to go to
        if (visited.count(pairhash(new_pos)) ||
                grid[new_pos.second][new_pos.first] == '#') continue;

        vector<pair<int, int>> path = path_to(grid, visited, new_pos, key);

        // Return if path is found
        if (path.size()) {
            path.push_back(pos);
            return path;
        }
    }

    // Base case
    return vector<pair<int, int>>();
}

int travel_to(vector<string>& grid, vector<char>& found, pair<int, int>& pos, char key, bool back=false) {
    unordered_set<uint64_t> visited;
    auto path = path_to(grid, visited, pos, key);
    for (int i = path.size() - 1; i >= 0; i--) {
        pair<int, int>& p = path[i];
        char& tile = grid[p.second][p.first];
        if (islower(tile) && tile != '.') { // Uneccessary?
            found.push_back(tile);
            tile = '.';
        }
    }

    if (back)
        return (path.size() - 1) * 2;
    else {
        pos = path.front();
        return path.size() - 1;
    }
}

unordered_map<uint64_t, char> get_triggers(
        vector<string>& grid,
        vector<string>& dependencies,
        pair<int, int> pos)
{
    unordered_map<uint64_t, char> triggers;
    unordered_set<char> remaining;

    for (string& dep : dependencies) {
        bool has_trigger = true;
        for (char key : dep) {
            if (isupper(key)) {
                has_trigger = false;
                break;
            }
        }

        if (has_trigger) {
            char to_key = dep.back();
            unordered_set<uint64_t> visited;
            auto path_to_key = path_to(grid, visited, pos, to_key);
        }
    }

    return triggers;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 0;

    vector<char> keyorder;
    unordered_set<uint64_t> visited;
    vector<string> dependencies = get_dependencies(input, visited, start);
    pair<int, int> pos = start;

    while (dependencies.size()) {

        vector<char> current_deps = current_dependencies(dependencies);

        if (current_deps.size() == 0) {
            for (string& s : dependencies) {
                current_deps.push_back(s.back());
            }
        }

        char closest_key = current_deps[0];
        int closest_dist = 1 << 30;
        for (char key : current_deps) {
            visited.clear();
            int dist = path_to(input, visited, pos, key).size() - 1;
            if (dist < closest_dist) {
                closest_key = key;
                closest_dist = dist;
            }
        }

        ans += travel_to(input, keyorder, pos, closest_key);

        for (char key : keyorder) {
            unlock_key(dependencies, key);
        }
    }

    //for (char c : keyorder)
    //    cout << c << endl;

    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = 0;
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
