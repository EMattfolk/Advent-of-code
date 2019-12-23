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

pair<int, int> start = { 0, 0 };
int min_dist = 1 << 30;
string keys = "";
unordered_map<string, int> states;


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
        if (dependencies[i].size() == 0) {
            dependencies.erase(dependencies.begin() + i);
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

vector<char> visible_keys(vector<string>& dependencies) {
    vector<char> visible;
    for (string& dependency : dependencies) {
        if (isupper(dependency[0])) continue;
        visible.push_back(dependency[0]);
    }

    return visible;
}

// Returns a path to a key with ends inclusive. size()-1 steps.
vector<pair<int, int>> path_to(
        vector<string>& grid,
        pair<int, int> init_pos,
        char key)
{
    unordered_set<uint64_t> visited;
    unordered_map<uint64_t, pair<int, int>> prev;

    queue<pair<int, int>> to_visit;
    to_visit.push(init_pos);
    visited.insert(pairhash(init_pos));

    while (to_visit.size()) {
        pair<int, int> pos = to_visit.front();
        to_visit.pop();

        // Done?
        if (grid[pos.second][pos.first] == key) {
            vector<pair<int, int>> path = { pos };
            while (prev.count(pairhash(pos))) {
                pos = prev[pairhash(pos)];
                path.push_back(pos);
            }
            return path;
        }

        pair<int, int> dir = { 1, 0 };

        for (int i = 0; i < 4; i++) {

            // New position
            pair<int, int> new_pos = { pos.first + dir.first, pos.second + dir.second };
            dir = rotate_dir(dir);

            // Avoid places we don't want to go to
            if (visited.count(pairhash(new_pos)) ||
                    grid[new_pos.second][new_pos.first] == '#') continue;

            to_visit.push(new_pos);
            prev[pairhash(new_pos)] = pos;
            visited.insert(pairhash(new_pos));
        }
    }

    // Base case
    return vector<pair<int, int>>();
}

void find_dist(Input& input,
        char pos,
        vector<string>& dependencies,
        vector<vector<int>>& dists,
        int current_dist=0)
{
    if (dependencies.size() == 0) {
        if (current_dist < min_dist) {
            min_dist = current_dist;
        }
        return;
    }

    string state = "";
    for (string& s : dependencies) state += s;
    state.push_back(pos);

    if (states.count(state)) {
        if (states[state] <= current_dist) return;
        else states[state] = current_dist;
    } else {
        states[state] = current_dist;
    }

    auto visible = visible_keys(dependencies);
    for (char key : visible) {
        int dist = dists[keys.find(key)][keys.find(pos)];
        vector<string> current_dep = dependencies;
        unlock_key(current_dep, key);
        find_dist(input, key, current_dep, dists, dist + current_dist);
    }
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    unordered_set<uint64_t> visited;
    unordered_map<char, pair<int, int>> positions;
    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[y].size(); x++) {
            if (islower(input[y][x])) {
                keys.push_back(input[y][x]);
            }
        }
    }

    for (char key : keys) {
        auto path = path_to(input, start, key);
        positions[key] = path[0];
    }

    vector<vector<int>> distances;
    for (uint32_t i = 0; i < keys.size(); i++) {
        distances.push_back(vector<int>());
        for (uint32_t j = 0; j < keys.size(); j++) {
            distances[i].push_back(0);
        }
    }

    for (uint32_t i = 0; i < distances.size(); i++) {
        for (uint32_t j = i; j < distances.size(); j++) {
            int dist = path_to(input, positions[keys[i]], keys[j]).size() - 1;
            distances[i][j] = dist;
            distances[j][i] = dist;
        }
    }

    visited.clear();
    vector<string> dependencies = get_dependencies(input, visited, start);
    auto visible = visible_keys(dependencies);
    for (char key : visible) {
        visited.clear();
        int dist = path_to(input, start, key).size() - 1;
        vector<string> current_dep = dependencies;
        unlock_key(current_dep, key);
        find_dist(input, key, current_dep, distances, dist);
    }

    return min_dist;
}

unordered_map<char, int> key_quadrant;
unordered_map<char, pair<int, int>> key_pos;
unordered_map<uint64_t, char> pos_to_key;
pair<int, int> starts[4];

void find_dist2(Input& input,
        pair<int, int> pos[4],
        vector<string> dependencies[4],
        vector<vector<int>>& dists,
        int current_dist=0)
{
    if (dependencies[0].size() == 0 &&
            dependencies[1].size() == 0 &&
            dependencies[2].size() == 0 &&
            dependencies[3].size() == 0) {
        if (current_dist < min_dist) {
            min_dist = current_dist;
        }
        return;
    }

    string state = "";
    for (int i = 0; i < 4; i++) {
        for (string& s : dependencies[i]) state += s;
    }
    for (int i = 0; i < 4; i++) {
        if (pos_to_key.count(pairhash(pos[i])))
            state.push_back(pos_to_key[pairhash(pos[i])]);
        else
            state.push_back('@');
    }

    if (states.count(state)) {
        if (states[state] <= current_dist) return;
        else states[state] = current_dist;
    } else {
        states[state] = current_dist;
    }

    vector<char> visible;
    for (int i = 0; i < 4; i++) {
        for (char k : visible_keys(dependencies[i])) visible.push_back(k);
    }
    for (char key : visible) {
        int quadrant = key_quadrant[key];
        int pos_index;
        pair<int, int> k_pos;
        if (pos_to_key.count(pairhash(pos[quadrant]))) {
            pos_index = keys.find(pos_to_key[pairhash(pos[quadrant])]);
        } else {
            pos_index = dists.size() - 1;
        }
        k_pos = key_pos[key];

        int dist = dists[keys.find(key)][pos_index];
        vector<string> current_dep0 = dependencies[0];
        vector<string> current_dep1 = dependencies[1];
        vector<string> current_dep2 = dependencies[2];
        vector<string> current_dep3 = dependencies[3];
        unlock_key(dependencies[0], key);
        unlock_key(dependencies[1], key);
        unlock_key(dependencies[2], key);
        unlock_key(dependencies[3], key);
        pair<int, int> current_pos = pos[quadrant];
        pos[quadrant] = k_pos;
        find_dist2(input, pos, dependencies, dists, dist + current_dist);
        dependencies[0] = current_dep0;
        dependencies[1] = current_dep1;
        dependencies[2] = current_dep2;
        dependencies[3] = current_dep3;
        pos[quadrant] = current_pos;
    }
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {

    min_dist = 1 << 20;
    states.clear();

    input[start.second][start.first - 1] = '#';
    input[start.second][start.first + 1] = '#';
    input[start.second - 1][start.first] = '#';
    input[start.second + 1][start.first] = '#';

    starts[0] = { start.first - 1, start.second - 1 };
    starts[1] = { start.first + 1, start.second - 1 };
    starts[2] = { start.first - 1, start.second + 1 };
    starts[3] = { start.first + 1, start.second + 1 };

    input[starts[0].second][starts[0].first] = '@';
    input[starts[1].second][starts[1].first] = '@';
    input[starts[2].second][starts[2].first] = '@';
    input[starts[3].second][starts[3].first] = '@';

    vector<string> deps[4];

    unordered_set<uint64_t> visited;
    for (int i = 0; i < 4; i++) {
        visited.clear();
        deps[i] = get_dependencies(input, visited, starts[i]);
    }

    for (char key : keys) {
        vector<pair<int, int>> path;
        for (int i = 0; i < 4; i++) {
            path = path_to(input, starts[i], key);
            if (path.size()) {
                key_quadrant[key] = i;
                break;
            }
        }

        key_pos[key] = path[0];
        pos_to_key[pairhash(path[0])] = key;
    }

    keys += '@';
    vector<vector<int>> distances;
    for (uint32_t i = 0; i < keys.size(); i++) {
        distances.push_back(vector<int>());
        for (uint32_t j = 0; j < keys.size(); j++) {
            distances[i].push_back(0);
        }
    }

    for (uint32_t i = 0; i < distances.size() - 1; i++) {
        for (uint32_t j = i; j < distances.size() - 1; j++) {
            if (key_quadrant[keys[i]] != key_quadrant[keys[j]]) continue;
            int dist = path_to(input, key_pos[keys[i]], keys[j]).size() - 1;
            distances[i][j] = dist;
            distances[j][i] = dist;
        }
    }

    for (uint32_t i = 0; i < distances.size() - 1; i++) {
        int dist = path_to(input, key_pos[keys[i]], '@').size() - 1;
        distances[i][distances.size() - 1] = dist;
        distances[distances.size() - 1][i] = dist;
    }

    find_dist2(input, starts, deps, distances);

    return min_dist;
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
