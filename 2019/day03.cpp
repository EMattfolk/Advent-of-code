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
};

struct Wire {
    Vec2 start;
    Vec2 end;
    int length;
    bool horizontal;

    bool crosses(const Wire& other) {
#define CROSS(P, Q) (((P).x * (Q).y) - ((P).y * (Q).x))
#define TO(P, Q) {((Q).x - (P).x), ((Q).y - (P).y)}
        Vec2 ab = TO(start, end);
        Vec2 cd = TO(other.start, other.end);

        if (CROSS(ab, cd) == 0)
            return false;

        Vec2 ac = TO(start, other.start);

        double s = 1.0 * CROSS(ac, cd) / CROSS(ab, cd);
        double t = 1.0 * CROSS(ac, ab) / CROSS(ab, cd);

        return s >= 0 && s <= 1 && t >= 0 && t <= 1;
    }
};

using Input = pair<vector<Wire>, vector<Wire>>;
using Answer = int;

void add_path(vector<Wire>& wire, string& path) {
    Vec2 pos = { 0, 0 };
    size_t index = 0;
    while (true) {
        char dir = path[0];
        path = path.substr(1);
        int length = stoi(path, &index);

        Vec2 start = pos;

        bool horizontal;
        if (dir == 'U') {
            pos.y += length;
            horizontal = false;
        } else if (dir == 'D') {
            pos.y -= length;
            horizontal = false;
        } else if (dir == 'L') {
            pos.x -= length;
            horizontal = true;
        } else {
            pos.x += length;
            horizontal = true;
        }

        Vec2 end = pos;

        wire.push_back({ start, end, length, horizontal });

        if (index + 1 >= path.size()) break;
        path = path.substr(index + 1);
    }
}

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

    return input;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 1 << 30;
    int len1 = 0;
    for (Wire wire1 : input.first) {
        int len2 = 0;
        for (Wire wire2 : input.second) {
            if (wire1.crosses(wire2)) {
                int dist;
                int combined_length = len1 + len2;
                Vec2 intersection;
                if (wire1.horizontal) {
                    intersection = { wire2.start.x, wire1.start.y };
                    combined_length += abs(wire2.start.y - intersection.y);
                    combined_length += abs(wire1.start.x - intersection.x);
                } else {
                    intersection = { wire1.start.x, wire2.start.y };
                    combined_length += abs(wire1.start.y - intersection.y);
                    combined_length += abs(wire2.start.x - intersection.x);
                }
                dist = abs(intersection.x) + abs(intersection.y);
                if (dist < ans) {
                    ans = dist;
                }
                if (combined_length < best_intersection) {
                    best_intersection = combined_length;
                }
            }
            len2 += wire2.length;
        }
        len1 += wire1.length;
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
