#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

//#define OUTPUT

using namespace std;
using Input = vector<int64_t>;
using Answer = int64_t;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    int64_t temp;
    while (is >> temp) {
        input.push_back(temp);
        is.ignore(1);
    }
    is.close();

    while (input.size() < 30000) input.push_back(0);

    return input;
}

uint64_t relative_base = 0;
uint64_t program_index = 0;

void add(int64_t a, int64_t b, int64_t& c) {
    c = a + b;
}

void mul(int64_t a, int64_t b, int64_t& c) {
    c = a * b;
}

void jit(uint64_t& instr, int64_t a, int64_t b) {
    if (a) instr = b;
}

void jif(uint64_t& instr, int64_t a, int64_t b) {
    if (!a) instr = b;
}

void les(int64_t a, int64_t b, int64_t& c) {
    c = a < b;
}

void equ(int64_t a, int64_t b, int64_t& c) {
    c = a == b;
}

int64_t& get_value(Input& program, int64_t mode, int64_t& value) {
    if (mode == 0) return program[value];
    else if (mode == 1) return value;
    else return program[relative_base + value];
}

Answer run_program(Input& program, int64_t write) {
    Answer res = 0;
    while (true) {
        int64_t opcode = program[program_index] % 100;
        if (opcode == 99) {
            return -1;
        }

        int64_t mode1 = (program[program_index] / 100) % 10;
        int64_t& arg1 = get_value(program, mode1, program[program_index+1]);
        if (opcode == 3) {
            arg1 = write;
            program_index += 2;
            continue;
        } else if (opcode == 4) {
            res = arg1;
            program_index += 2;
            break;
        } else if (opcode == 9) {
            relative_base += arg1;
            program_index += 2;
            continue;
        }

        int64_t mode2 = (program[program_index] / 1000) % 10;
        int64_t& arg2 = get_value(program, mode2, program[program_index+2]);
        if (opcode == 5) {
            program_index += 3;
            jit(program_index, arg1, arg2);
            continue;
        } else if (opcode == 6) {
            program_index += 3;
            jif(program_index, arg1, arg2);
            continue;
        }

        uint64_t mode3 = (program[program_index] / 10000) % 10;
        int64_t& arg3 = get_value(program, mode3, program[program_index+3]);
        if (opcode == 1) {
            add(arg1, arg2, arg3);
        } else if (opcode == 2) {
            mul(arg1, arg2, arg3);
        } else if (opcode == 7) {
            les(arg1, arg2, arg3);
        } else if (opcode == 8) {
            equ(arg1, arg2, arg3);
        }
        program_index += 4;
    }
    return res;
}

uint64_t pairhash(const pair<int, int>& pos) {
    const pair<int, int>* addr = &pos;
    return *((uint64_t*)addr);
}

pair<int, int> pairunhash(const uint64_t& pos) {
    const uint64_t* addr = &pos;
    return *((pair<int, int>*)addr);
}

int dir_to_code(pair<int, int> dir) {
    if (dir.second == 1) return 1;
    else if (dir.second == -1) return 2;
    else if (dir.first == -1) return 3;
    else return 4;
}

pair<int, int> rotate_dir(pair<int, int> dir) {
    return { -dir.second, dir.first };
}

vector<pair<int, int>> dirs = {{ 0, 1 }, { 0, -1 }, { -1, 0 }, { 1, 0 }};

pair<int, int> oxygen = { 0, 0 };
unordered_map<uint64_t, int> map;

int traverse(Input& input,
        unordered_set<uint64_t>& visited,
        pair<int, int> pos,
        pair<int, int> from_dir,
        int depth=0) {

    visited.insert(pairhash(pos));

    int res = -1;

    for (auto& dir : dirs) {
        pair<int, int> new_pos = { pos.first + dir.first, pos.second + dir.second };
        if (visited.count(pairhash(new_pos))) continue;
        int tile = run_program(input, dir_to_code(dir));
        map[pairhash(new_pos)] = tile;

        if (tile == 0) continue;
        if (tile == 2) {
            oxygen = new_pos;
            res = depth + 1;
        }

        int d = traverse(input, visited, new_pos, dir, depth+1);
        if (d != -1) res = d;
    }

    run_program(input, dir_to_code(rotate_dir(rotate_dir(from_dir))));
    return res;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Input program = input;
    unordered_set<uint64_t> visited;
    Answer ans = traverse(input, visited, { 0, 0 }, { 0, 0 });

#ifdef OUTPUT
    string grid(51*51, ' ');
    for (int i = 50; i < grid.size(); i += 51) grid[i] = '\n';
    for (auto& p : map) {
        pair<int, int> pos = pairunhash(p.first);
        grid[(pos.second + 25) * 51 + (pos.first + 25)] =
            (p.second == 0 ? '#' : (p.second == 2 ? 'O' : ' '));
    }
    cout << grid << endl;
#endif

    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = -1;

    queue<pair<int, int>> to_visit;
    unordered_set<uint64_t> visited;

    to_visit.push(oxygen);
    int to_fill = 1;

    while (to_visit.size()) {
        pair<int, int> pos = to_visit.front();
        to_visit.pop();

        visited.insert(pairhash(pos));
        for (auto& dir : dirs) {
            pair<int, int> new_pos = { pos.first + dir.first, pos.second + dir.second };
            if (visited.count(pairhash(new_pos)) || map[pairhash(new_pos)] == 0)
                continue;
            to_visit.push(new_pos);
        }

        if (--to_fill == 0) {
            to_fill = to_visit.size();
            ans++;
        }
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
