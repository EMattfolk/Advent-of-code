#include "stdio.h"
#include "string.h"

char* solve_day_20(char* input) {

	int div_sum(int n) {

		int sum = 1;

		for (int i = 2; i * i <= n; i++) {
			int mult = 1;
			int part_sum_1 = 1;
			while (n % i == 0) {
				mult *= i;
				n /= i;
				part_sum_1 += mult;
			}

			sum *= part_sum_1;
		}

		if (n != 1) {
			sum *= n + 1;
		}

		return sum;
	}

	int lim = atoi(input);
	int ans1 = 0;
	int ans2 = 0;

	int i = 0;
	while (ans1 == 0) {

		if (div_sum(i) * 10 >= lim) {
			ans1 = i;
		}

		i++;
	}

	int delivered[1000000];
	memset(delivered, 0, sizeof(delivered));

	for (int i = 1; i < 1000000; i++) {
		int house = i;
		for (int j = 1; j <= 50 && house < 1000000; j++) {
			delivered[house] += i;
			house += i;
		}
	}

	for (int i = 1; i < 1000000; i++) {
		if (delivered[i] * 11 >= lim) {
			ans2 = i;
			break;
		}
	}
	
	sprintf(input, "%d, %d", ans1, ans2);

    return input;
}
