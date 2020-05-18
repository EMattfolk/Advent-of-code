#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

char* solve_day_02(char* input) {
	char* save_ptr;
	char* tok = strtok_r(input, "\n", &save_ptr);
	int wrap = 0;
	int ribbon = 0;

	while (tok) { 
		int l = 0;
		int w = 0;
		int h = 0;
		char* temp = strtok(tok, "x");
		l = atoi(temp);
		temp = strtok(NULL, "x");
		w = atoi(temp);
		temp = strtok(NULL, "x");
		h = atoi(temp);
		tok = strtok_r(NULL, "\n", &save_ptr);

		int min_side = MIN(MIN(l*w, w*h), h*l);

		wrap += 2*l*w + 2*w*h + 2*h*l + min_side;
		ribbon += 2*l + 2*w + 2*h - 2*MAX(MAX(w, l), h) + l*w*h;
	}

	sprintf(input, "%d, %d", wrap, ribbon);

    return input;
}
