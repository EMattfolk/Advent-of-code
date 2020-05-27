#include "stdio.h"
#include "string.h"

char* solve_day_18(char* input) {

	char *grid[100];
	char grid_copy[100][101];

	char *tok = strtok(input, "\n");

	int i = 0;
	while (tok != NULL) {
		grid[i] = tok;
		strcpy(grid_copy[i++], tok);
		tok = strtok(NULL, "\n");
	}

	bool in_bounds(int x, int y) {
		return x >= 0 && x < 100 && y >= 0 && y < 100;
	}

	void step(bool corners) {

		if (corners) {
			grid[0][0] = '#';
			grid[99][0] = '#';
			grid[0][99] = '#';
			grid[99][99] = '#';
		}

		char buf1[101];
		char buf2[101];

		buf1[100] = '\0';
		buf2[100] = '\0';

		char *prev_buf = buf2;
		char *buf = buf1;
		for (int y = 0; y < 100; y++) {
			for (int x = 0; x < 100; x++) {
				int neighbors = 0;
				for (int yo = -1; yo <= 1; yo++) {
					for (int xo = -1; xo <= 1; xo++) {
						if (xo == 0 && yo == 0) {
							continue;
						}

						if (in_bounds(x + xo, y + yo)) {
							neighbors += grid[y + yo][x + xo] == '#';
						}
					}
				}

				if (grid[y][x] == '.') {
					if (neighbors == 3) {
						buf[x] = '#';
					} else {
						buf[x] = grid[y][x];
					}
				} else if (neighbors != 2 && neighbors != 3) {
					buf[x] = '.';
				} else {
					buf[x] = grid[y][x];
				}
			}

			if (y > 0) {
				strcpy(grid[y-1], prev_buf);
			}

			if (y == 99) {
				strcpy(grid[y], buf);
			}

			char *temp = prev_buf;
			prev_buf = buf;
			buf = temp;
		}
	}

	for (int i = 0; i < 100; i++) {
		step(false);
	}

	int lights1 = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			lights1 += grid[i][j] == '#';
		}
	}

	for (int i = 0; i < 100; i++) {
		strcpy(grid[i], grid_copy[i]);
	}

	for (int i = 0; i < 100; i++) {
		step(true);
	}

	grid[0][0] = '#';
	grid[99][0] = '#';
	grid[0][99] = '#';
	grid[99][99] = '#';

	int lights2 = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			lights2 += grid[i][j] == '#';
		}
	}

	sprintf(input, "%d, %d", lights1, lights2);

    return input;
}
