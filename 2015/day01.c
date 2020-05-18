#include "stdio.h"
#include "string.h"

char* solve_day_01(char* input) {
	int ans1 = 0;
	int ans2 = 1, change = 1;
	char c;
	while ((c = *input++)) {
		ans1 += c == '(' ? 1 : -1;
		if (ans1 == -1) {
			change = 0;
		}
		ans2 += change;
	}
	sprintf(input, "%d, %d", ans1, ans2);
	return input;
}
