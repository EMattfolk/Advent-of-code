#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <utility>
#include <functional>
#include <unordered_map>
#include <cmath>
#include <vector>

using namespace std;

struct Vec2 {
    int x;
    int y;

    bool operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }
};

template <>
struct std::hash<Vec2> {
    size_t operator()(const Vec2& p) const {
        hash<int> hasher;
        return hasher(p.y) * 1000 + hasher(p.x);
    }
};

using Input = pair<vector<Vec2>, vector<Vec2>>;
using Answer = int;

void add_path(vector<Vec2>& wire, string& path) {
    Vec2 pos = { 0, 0 };
    size_t index = 0;
    while (true) {
        char dir = path[0];
        path = path.substr(1);
        int length = stoi(path, &index);

        for (int i = 0; i < length; i++) {
            if (dir == 'U')
                pos.y++;
            else if (dir == 'D')
                pos.y--;
            else if (dir == 'L')
                pos.x--;
            else if (dir == 'R')
                pos.x++;
            else
                cout << "Error" << endl;

            wire.push_back(pos);
        }
        if (index + 1 >= path.size()) break;
        path = path.substr(index + 1);
    }
}

unordered_map<Vec2, int> paths;
int best_intersection = 1 << 30;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    string temp;
    is >> temp;
    add_path(input.first, temp);
    is >> temp;
    add_path(input.second, temp);
    is.close();

    paths.reserve(input.first.size());
    for (size_t i = 0; i < input.first.size(); i++) {
        paths[input.first[i]] = i;
    }

    return input;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 1 << 30;
    for (size_t i = 0; i < input.second.size(); i++) {
        Vec2 pos = input.second[i];
        if (paths.count(pos)) {
            int dist = abs(pos.x) + abs(pos.y);
            int len = i + paths[pos] + 2;
            if (dist < ans)
                ans = dist;
            if (len < best_intersection)
                best_intersection = len;
        }
    }
    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = best_intersection;
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
