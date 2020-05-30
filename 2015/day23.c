#include "stdio.h"
#include "string.h"

char* solve_day_23(char* input) {

	long a1 = 0;
	long a2 = 1;

	long *a = &a1;

	inline char* next() {
		return strtok(NULL, " ,\n+1234567890");
	}

	char *tok = strtok(input, " ,\n+1234567890");

	while (true) {
		if (!strcmp(tok, "jmp")) {
			tok = next();
			a = &a2;
			continue;
		}

		char *reg = next();

		if (!strcmp(reg, "b")) {
			break;
		}

		if (!strcmp(tok, "inc")) {
			(*a)++;
		} else if (!strcmp(tok, "tpl")) {
			*a *= 3;
		}

		tok = next();
	}

	int collatz(long a) {

		int b = 0;

		while (a != 1) {
			b++;
			if (a % 2 == 0) {
				a /= 2;
			} else {
				a *= 3;
				a++;
			}
		}

		return b;
	}

	sprintf(input, "%d, %d", collatz(a1), collatz(a2));

    return input;
}
