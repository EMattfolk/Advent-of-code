#include "stdio.h"
#include "string.h"

int day_24_cmp(const void* a, const void* b) {
	return -(*(int*)a - *(int*)b);
}

char* solve_day_24(char* input) {

	int weights[100];
	int weight_count = 0;
	int weight_sum = 0;

	char *tok = strtok(input, "\n");

	while (tok != NULL) {

		weights[weight_count] = atoi(tok);
		weight_sum += weights[weight_count++];

		tok = strtok(NULL, "\n");
	}

    qsort(weights, weight_count, sizeof(int), day_24_cmp);

	int smallest_group = 1 << 30;
	long lowest_qe = 1 << 30;

	int limit = weight_sum / 3;

	// For some reason, finding one group means that there exists
	// other groups that sum to the same number using the leftover numbers.
	// Might have something to do with prime numbers.

	void recurse_groups(int index, int sum, int size, long qe) {
		if (sum > limit ||
				index > weight_count ||
				size > smallest_group ||
				(size == smallest_group && qe >= lowest_qe)) {
			return;
		} else if (sum == limit) {
			smallest_group = size;
			lowest_qe = qe;
			return;
		}

		recurse_groups(index + 1, sum + weights[index], size + 1, qe * weights[index]);
		recurse_groups(index + 1, sum, size, qe);
	}

	recurse_groups(0, 0, 0, 1);

	long ans1 = lowest_qe;

	smallest_group = 1 << 30;
	lowest_qe = 1 << 30;

	limit = weight_sum / 4;

	recurse_groups(0, 0, 0, 1);

	long ans2 = lowest_qe;

	sprintf(input, "%ld, %ld", ans1, ans2);

    return input;
}
