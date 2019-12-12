#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <functional>
#include <unordered_map>

struct Planet {
    int x;
    int y;
    int z;
    int xv = 0;
    int yv = 0;
    int zv = 0;
};

using namespace std;
using Input = vector<Planet>;
using Answer = uint64_t;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    ifstream is(filename);
    while (is.ignore(3)) {
        int x, y, z;
        is >> x;
        is.ignore(4);
        is >> y;
        is.ignore(4);
        is >> z;
        is.ignore(2);
        input.push_back({ x, y, z });
    }
    is.close();

    return input;
}

void step(Input& input) {
    for (uint32_t i = 0; i < input.size(); i++) {
        Planet& planet1 = input[i];
        for (uint32_t j = i+1; j < input.size(); j++) {
            Planet& planet2 = input[j];
            if (planet1.x < planet2.x) {
                planet1.xv++;
                planet2.xv--;
            } else if (planet1.x > planet2.x) {
                planet1.xv--;
                planet2.xv++;
            }
            if (planet1.y < planet2.y) {
                planet1.yv++;
                planet2.yv--;
            } else if (planet1.y > planet2.y) {
                planet1.yv--;
                planet2.yv++;
            }
            if (planet1.z < planet2.z) {
                planet1.zv++;
                planet2.zv--;
            } else if (planet1.z > planet2.z) {
                planet1.zv--;
                planet2.zv++;
            }
        }
    }
    for (Planet& planet : input) {
        planet.x += planet.xv;
        planet.y += planet.yv;
        planet.z += planet.zv;
    }
}

int energy(Planet& planet) {
    return (abs(planet.x) + abs(planet.y) + abs(planet.z)) *
        (abs(planet.xv) + abs(planet.yv) + abs(planet.zv));
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 0;
    Input planets = input;
    for (int i = 0; i < 1000; i++) {
        step(planets);
    }
    for (Planet& planet : planets) {
        ans += energy(planet);
    }
    return ans;
}

struct State {
    int pos[4];
    int vel[4];
    
    bool operator==(const State& other) {
        return pos[0] == other.pos[0] && pos[1] == other.pos[1] &&
            pos[2] == other.pos[2] && pos[3] == other.pos[3] &&
            vel[0] == other.vel[0] && vel[1] == other.vel[1] &&
            vel[2] == other.vel[2] && vel[3] == other.vel[3];
    }

    bool operator!=(const State& other) {
        return !(*this == other);
    }

    void next() {
        for (int i = 0; i < 4; i++) {
            for (int j = i+1; j < 4; j++) {
                if (pos[i] < pos[j]) {
                    vel[i]++;
                    vel[j]--;
                } else if (pos[i] > pos[j]) {
                    vel[i]--;
                    vel[j]++;
                }
            }
        }
        for (int i = 0; i < 4; i++) {
            pos[i] += vel[i];
        }
    }
};

bool operator==(State me, State other) {
    return me.pos[0] == other.pos[0] && me.pos[1] == other.pos[1] &&
        me.pos[2] == other.pos[2] && me.pos[3] == other.pos[3] &&
        me.vel[0] == other.vel[0] && me.vel[1] == other.vel[1] &&
        me.vel[2] == other.vel[2] && me.vel[3] == other.vel[3];
}

namespace std {
template <>
struct hash<State>
{
    size_t operator()(const State& k) const
    {
        return k.pos[0] ^ (k.pos[1] << 1) ^ (k.pos[2] << 2) ^ (k.pos[3] << 3) ^
            (k.vel[0] << 4) ^ (k.vel[1] << 5) ^ (k.vel[2] << 6) ^ (k.vel[3] << 7);
    }
};
}

uint64_t gcd(uint64_t a, uint64_t b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {

    State statex;
    statex.pos[0] = input[0].x;
    statex.pos[1] = input[1].x;
    statex.pos[2] = input[2].x;
    statex.pos[3] = input[3].x;
    statex.vel[0] = input[0].xv;
    statex.vel[1] = input[1].xv;
    statex.vel[2] = input[2].xv;
    statex.vel[3] = input[3].xv;
    State init_state = statex;

    uint64_t lengthx = 0;
    while (statex != init_state || lengthx == 0) {
        statex.next();
        lengthx++;
    }


    State statey;
    statey.pos[0] = input[0].y;
    statey.pos[1] = input[1].y;
    statey.pos[2] = input[2].y;
    statey.pos[3] = input[3].y;
    statey.vel[0] = input[0].yv;
    statey.vel[1] = input[1].yv;
    statey.vel[2] = input[2].yv;
    statey.vel[3] = input[3].yv;
    init_state = statey;

    uint64_t lengthy = 0;
    while (statey != init_state || lengthy == 0) {
        statey.next();
        lengthy++;
    }

    State statez;
    statez.pos[0] = input[0].z;
    statez.pos[1] = input[1].z;
    statez.pos[2] = input[2].z;
    statez.pos[3] = input[3].z;
    statez.vel[0] = input[0].zv;
    statez.vel[1] = input[1].zv;
    statez.vel[2] = input[2].zv;
    statez.vel[3] = input[3].zv;
    init_state = statez;

    uint64_t lengthz = 0;
    while (statez != init_state || lengthz == 0) {
        statez.next();
        lengthz++;
    }

    Answer ans = lengthx * lengthy * lengthz;

    uint64_t d = gcd(lengthx, gcd(lengthy, lengthz));
    ans /= d*d;

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
