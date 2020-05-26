#include "stdio.h"
#include "string.h"

char* solve_day_10(char* input) {
	input[strlen(input) - 1] = '\0';

	char *buf1 = calloc(10000000, sizeof(char));
	char *buf2 = calloc(10000000, sizeof(char));

	sprintf(buf1, "%s", input);

	char *from = buf1;
	char *to = buf2;
	char *from_it = from;
	char *to_it = to;

	int ans1 = 0;

	for (int i = 0; i < 50; i++) {

		if (i == 40) {
			ans1 = strlen(from);
		}

		char a;
		while ((a = *from_it++)) {
			if (a != *from_it) {
				*to_it++ = '1';
			} else if (a != *++from_it) {
				*to_it++ = '2';
			} else {
				from_it++;
				*to_it++ = '3';
			}
			*to_it++ = a;
		}

		char *temp = from;
		from = to;
		to = temp;
		from_it = from;
		to_it = to;
	}

	//printf("'%s'\n", buf1);

	sprintf(input, "%d, %ld", ans1, strlen(from));

	free(buf1);
	free(buf2);
	
    return input;
}
