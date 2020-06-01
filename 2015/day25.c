#include "stdio.h"
#include "string.h"

char* solve_day_25(char* input) {
	const char *delim = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,\n ";

	int row = atoi(strtok(input, delim));
	int col = atoi(strtok(NULL, delim));

	void next(int *row, int *col) {
		(*row)--;
		(*col)++;

		if (*row == 0) {
			*row = *col;
			*col = 1;
		}
	}

	int r = 1;
	int c = 1;

	long code = 20151125;

	// Do pow mod here for that sweet O(log N)

	while (r != row || c != col) {
		next(&r, &c);
		code = (code * 252533) % 33554393;
	}

	sprintf(input, "%ld, %d", code, row);

    return input;
}
