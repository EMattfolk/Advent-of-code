#include "stdio.h"
#include "string.h"

char* solve_day_08(char* input) {
	char *tok = strtok(input, "\n");

	int ans1 = 0;
	int ans2 = 0;

	while (tok != NULL) {

		ans1 += 2;
		ans2 += 2;

		char *it = tok;

		char c;
		while ((c = *it++) != '\0') {
			ans2 += c == '\\' || c == '"';
			if (c == '\\') {
				c = *it++;
				if (c == '"' || c == '\\') {
					ans1++;
					ans2++;
				} else if (c == 'x') {
					ans1 += 3;
				}
			}
		}

		tok = strtok(NULL, "\n");
	}

	sprintf(input, "%d, %d", ans1, ans2);

    return input;
}
