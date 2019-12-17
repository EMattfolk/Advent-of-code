#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

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

    while (input.size() < 4000) input.push_back(0);

    return input;
}

class IntCode {
public:

    IntCode(vector<int64_t>& program) : program(program) {}

    int64_t run(string& input) {
        int64_t res = 0;
        while (true) {
            int64_t opcode = program[program_index] % 100;
            if (opcode == 99) {
                halted = true;
                return -1;
            }

            int64_t mode1 = (program[program_index] / 100) % 10;
            int64_t& arg1 = get_value(program, mode1, program[program_index+1]);
            if (opcode == 3) {
                arg1 = input[input_index++];
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

    int64_t& get_value(Input& program, int64_t mode, int64_t& value) {
        if (mode == 0) return program[value];
        else if (mode == 1) return value;
        else return program[relative_base + value];
    }

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

    vector<int64_t> program;
    bool halted = false;
    uint64_t relative_base = 0;
    uint64_t program_index = 0;
    uint32_t input_index = 0;
};

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

bool in_bounds(vector<string>& grid, int x, int y) {
    return x >= 0 && y >= 0 && x < (int)grid[0].size() && y < (int)grid.size();
}

bool at_edge(vector<string>& grid, pair<int, int>& pos) {
    int c = 0;
    if (in_bounds(grid, pos.first, pos.second + 1))
        c += grid[pos.second + 1][pos.first] == '#';
    if (in_bounds(grid, pos.first, pos.second - 1))
        c += grid[pos.second - 1][pos.first] == '#';
    if (in_bounds(grid, pos.first + 1, pos.second))
        c += grid[pos.second][pos.first + 1] == '#';
    if (in_bounds(grid, pos.first - 1, pos.second))
        c += grid[pos.second][pos.first - 1] == '#';
    return c == 1;
}

vector<string> seq;

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    IntCode program(input);
    vector<string> grid;
    string empt = "";
    char c;
    while ((c = program.run(empt)) != -1) {
        grid.push_back("");
        do {
            grid.back() += (char)c;
        } while ((c = program.run(empt)) != 10 && c != -1);
    }

    pair<int, int> pos;
    pair<int, int> dir = { 0, -1 };

    Answer ans = 0;
    for (uint32_t i = 1; i < grid.size() - 1; i++) {
        for (uint32_t j = 1; j < grid[i].size() - 1; j++) {
            if (grid[i][j] == '^') {
                pos = { j, i };
                grid[i][j] = '#';
            }
            if (grid[i][j] == '#' && grid[i-1][j] == '#' && grid[i+1][j] == '#'
                    && grid[i][j-1] == '#' && grid[i][j+1] == '#')
                ans += i*j;
        }
    }


#ifdef OUTPUT
    cout << endl;
    for (uint32_t i = 0; i < grid.size(); i++) {
        cout << grid[i] << endl;
    }
#endif

    int length = 0;
    do {
        pair<int, int> new_pos = { pos.first + dir.first, pos.second + dir.second };
        if (!in_bounds(grid, new_pos.first, new_pos.second) ||
                grid[new_pos.second][new_pos.first] != '#') {
            if (length > 0) {
                seq.push_back(to_string(length));
                length = 0;
            }
            dir = rotate_dir(dir);
            pair<int, int> r_pos = { pos.first + dir.first, pos.second + dir.second };
            if (grid[r_pos.second][r_pos.first] == '#') {
                seq.push_back("R");
            } else {
                seq.push_back("L");
                dir = rotate_dir(rotate_dir(dir));
            }
            new_pos = { pos.first + dir.first, pos.second + dir.second };
        }

        pos = new_pos;
        length++;

    } while (!at_edge(grid, pos));

    seq.push_back(to_string(length));

    return ans;
}

vector<string> remove_subseq(vector<string>& seq, int subs) {
    vector<string> new_seq;
    bool is_subseq = true;
    for (uint32_t i = subs; i <= seq.size() - subs; i++) {
        is_subseq = true;
        for (int j = 0; j < subs; j++) {
            if (seq[j] != seq[i+j]) {
                is_subseq = false;
                break;
            }
        }
        if (is_subseq) {
            i += subs - 1;
        } else {
            new_seq.push_back(seq[i]);
        }
    }

    // Trailing
    if (!is_subseq) {
        for (uint32_t i = seq.size() - subs + 1; i < seq.size(); i++) {
            new_seq.push_back(seq[i]);
        }
    }

    return new_seq;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {

    int A = 0, B = 0, C = 0;
    for (int i = 4; i <= 8; i += 2) {
        vector<string> iseq = remove_subseq(seq, i);
        for (int j = 4; j <= 8; j += 2) {
            vector<string> jseq = remove_subseq(iseq, j);
            for (int k = 4; k <= 8; k += 2) {
                vector<string> kseq = remove_subseq(jseq, k);
                if (kseq.size() == 0) {
                    A = i;
                    B = j;
                    C = k;
                    goto done;
                }
            }
        }
    }

done:
    vector<string> seqA, seqB, seqC;
    vector<string> temp_seq = seq;
    for (int j = 0; j < A; j++) {
        seqA.push_back(temp_seq[j]);
    }
    temp_seq = remove_subseq(temp_seq, A);
    for (int j = 0; j < B; j++) {
        seqB.push_back(temp_seq[j]);
    }
    temp_seq = remove_subseq(temp_seq, B);
    for (int j = 0; j < C; j++) {
        seqC.push_back(temp_seq[j]);
    }
    temp_seq = remove_subseq(temp_seq, C);

    string moves = "";
    for (uint32_t i = 0; i < seq.size();) {
        bool found = true;
        for (int j = 0; j < A; j++) {
            if (seqA[j] != seq[i+j]) {
                found = false;
                break;
            }
        }
        if (found) {
            moves += ",A";
            i += A;
            continue;
        }
        found = true;
        for (int j = 0; j < B; j++) {
            if (seqB[j] != seq[i+j]) {
                found = false;
                break;
            }
        }
        if (found) {
            moves += ",B";
            i += B;
            continue;
        }
        found = true;
        for (int j = 0; j < C; j++) {
            if (seqC[j] != seq[i+j]) {
                found = false;
                break;
            }
        }
        if (found) {
            moves += ",C";
            i += C;
            continue;
        }
    }

    moves = moves.substr(1);
    moves += '\n';
    for (int j = 0; j < A; j++) {
        if (j != 0) moves += ',';
        moves += seqA[j];
    }
    moves += '\n';
    for (int j = 0; j < B; j++) {
        if (j != 0) moves += ',';
        moves += seqB[j];
    }
    moves += '\n';
    for (int j = 0; j < C; j++) {
        if (j != 0) moves += ',';
        moves += seqC[j];
    }
    moves += '\n';
    moves += "n\n";

    IntCode program(input);
    program.program[0] = 2;
    Answer ans = 0;
    while (true) {
        int64_t res = program.run(moves);
        if (program.halted) break;
        ans = res;
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
