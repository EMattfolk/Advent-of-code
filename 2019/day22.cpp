#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;
using Input = vector<pair<int, int>>;
using Answer = int64_t;

const int STACK = 0;
const int CUT = 1;
const int INC = 2;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    string temp;
    while (is >> temp) {
        if (temp == "cut") {
            int value;
            is >> value;
            input.push_back({ CUT, value });
        } else if (temp == "deal") {
            is >> temp;
            if (temp == "into") {
                input.push_back({ STACK, 0 });
            } else {
                is >> temp;
                int value;
                is >> value;
                input.push_back({ INC, value });
            }
        }
    }
    is.close();

    return input;
}

inline __int128 mod(__int128 i, __int128 n) {
    return (i % n + n) % n;
}

pair<__int128, __int128> stack_card() {
    return { -1, -1 };
}

pair<__int128, __int128> cut_card(__int128 by) {
    return { 1, -by };
}

pair<__int128, __int128> inc_card(__int128 by) {
    return { by, 0 };
}

pair<__int128, __int128> comb_transform(
        pair<__int128, __int128> f,
        pair<__int128, __int128> g,
        __int128& size)
{
    return { mod(f.first * g.first, size), mod(f.first * g.second + f.second, size)};
}

__int128 apply_transform(pair<__int128, __int128>& transform,
        __int128 pos,
        __int128 size) {
    return mod(transform.first * pos + transform.second, size);
}


/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {

    // Every shuffle is ax+b
    pair<__int128, __int128> transform = { 1, 0 };
    __int128 size = 10007;

    for (auto instr : input) {
        __int128 n = instr.second;
        switch (instr.first) {
            case (STACK):
                transform = comb_transform(stack_card(), transform, size);
                break;
            case (CUT):
                transform = comb_transform(cut_card(n), transform, size);
                break;
            case (INC):
                transform = comb_transform(inc_card(n), transform, size);
                break;
        }
    }

    return apply_transform(transform, 2019, size);
}

__int128 pow(__int128 b, __int128 e, __int128 m) {
    __int128 res = 1;
    while (e) {
        if (e & 1)
            res = mod(res * b, m);
        b = mod(b * b, m);
        e >>= 1;
    }

    return res;
}

pair<__int128, __int128> inv_stack_card() {
    return { -1, -1 };
}

pair<__int128, __int128> inv_cut_card(__int128 by) {
    return { 1, by };
}

pair<__int128, __int128> inv_inc_card(__int128 by, __int128 size) {
    return { pow(by, size-2, size), 0 };
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {

    // Every shuffle is ax+b
    pair<__int128, __int128> base = { 1, 0 };
    __int128 size = 119315717514047LL;

    for (auto instr : input) {
        __int128 n = instr.second;
        switch (instr.first) {
            case (STACK):
                base = comb_transform(base, inv_stack_card(), size);
                break;
            case (CUT):
                base = comb_transform(base, inv_cut_card(n), size);
                break;
            case (INC):
                base = comb_transform(base, inv_inc_card(n, size), size);
                break;
        }
    }

    __int128 reps = 101741582076661LL;
    pair<__int128, __int128> transform = { 1, 0 };
    while (reps) {
        if (reps & 1)
            transform = comb_transform(base, transform, size);
        base = comb_transform(base, base, size);
        reps >>= 1;
    }

    return apply_transform(transform, 2020, size);
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
