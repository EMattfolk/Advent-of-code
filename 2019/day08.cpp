#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>

//#define OUTPUT

using namespace std;
using Input = vector<string>;
using Answer = int;

const unsigned int WIDTH = 25;
const unsigned int HEIGHT = 6;

/*
 * Read input from file.
 */
Input get_input(const char* filename) {
    Input input;
    string buf;
    ifstream is(filename);
    is >> buf;
    is.close();

    unsigned int i = 0;
    while (i < buf.size()) {
        input.push_back(buf.substr(i, WIDTH * HEIGHT));
        i += WIDTH * HEIGHT;
    }

    return input;
}

/*
 * Solve the first problem.
 */
Answer solve_first(Input& input) {
    Answer ans = 0;
    string* min_layer = &input[0];
    int min_zeroes = -1;
    for (string& layer : input) {
        int zeroes = 0;
        for (char c : layer) {
            zeroes += c == '0';
        }
        if (min_zeroes == -1 || zeroes < min_zeroes) {
            min_zeroes = zeroes;
            min_layer = &layer;
        }
    }

    int ones = 0;
    int twos = 0;
    for (char c : *min_layer) {
        ones += c == '1';
        twos += c == '2';
    }

    ans = ones * twos;

    return ans;
}

/*
 * Solve the second problem.
 */
Answer solve_second(Input& input) {
    Answer ans = 0;
    string& image = input[0];

    for (unsigned int j = 0; j < image.size(); j++) {
        for (unsigned int i = 0; i < input.size(); i++) {
            image[j] = (image[j] == '2' ? input[i][j] : image[j]);
        }
    }


#ifdef OUTPUT
    cout << endl;
    for (unsigned int i = 0; i < HEIGHT; i++) {
        for (unsigned int j = 0; j < WIDTH; j++) {
            cout << (image[i*WIDTH + j] == '1' ? '#' : ' ');
        }
        cout << endl;
    }
#endif

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
    first_answer += second_answer;

    auto end = chrono::high_resolution_clock::now();

    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end-start).count();

    cout << first_answer << ", " << "PCULA" << " - " << elapsed << "ms" << endl;

    return 0;
}
