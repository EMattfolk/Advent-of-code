#include "stdio.h"
#include "string.h"

char* solve_day_06(char* input) {
	bool grid[1000][1000];
	int brightness[1000][1000];

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			grid[i][j] = false;
			brightness[i][j] = 0;
		}
	}

	char* next() {
		return strtok(NULL, " ,\n");
	}

	char *tok = strtok(input, " ,\n");
	while (tok != NULL) {

		bool toggle = false;
		bool new_value = false;
		int x0, y0, x1, y1;

		if (tok[1] == 'o') {
			toggle = true;
		} else {
			tok = next();
			new_value = tok[1] == 'n';
		}

		x0 = atoi(next());
		y0 = atoi(next());
		next();
		x1 = atoi(next());
		y1 = atoi(next());

		if (toggle) {
			for (int y = y0; y <= y1; y++) {
				for (int x = x0; x <= x1; x++) {
					grid[y][x] = !grid[y][x];
					brightness[y][x] += 2;
				}
			}
		} else {
			int change = new_value ? 1 : -1;
			for (int y = y0; y <= y1; y++) {
				for (int x = x0; x <= x1; x++) {
					grid[y][x] = new_value;
					brightness[y][x] += change;
					brightness[y][x] = brightness[y][x] < 0 ? 0 : brightness[y][x];
				}
			}
		}

		tok = next();
	}

	int lights = 0;
	long bright = 0;

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			lights += grid[i][j];
			bright += brightness[i][j];
		}
	}

	sprintf(input, "%d, %ld", lights, bright);

    return input;
}
