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

	bool picked[100];

	memset(picked, 0, sizeof(picked));

	int smallest_group = 1 << 30;
	long lowest_qe = 1 << 30;

	int limit = weight_sum / 3;
	//int depth_limit = 1;

	// Not needed for some reason?
	//bool exists_other_group(int index, int sum, int depth) {
	//	if (sum == limit) {
	//		if (depth + 1 == depth_limit) {
	//			return true;
	//		} else {
	//			return exists_other_group(0, 0, depth + 1);
	//		}
	//	} else if (sum > limit || index >= weight_count) {
	//		return false;
	//	} else if (picked[index]) {
	//		return exists_other_group(index + 1, sum, depth);
	//	}

	//	picked[index] = true;
	//	bool exists = exists_other_group(index + 1, sum + weights[index], depth);
	//	picked[index] = false;

	//	return exists || exists_other_group(index + 1, sum, depth);
	//}

	void recurse_groups(int index, int sum) {
		if (sum == limit) {
			int size = 0;
			long qe = 1;

			for (int i = 0; i < weight_count; i++) {
				if (picked[i]) {
					qe *= weights[i];
					size++;
				}
			}

			//if (exists_other_group(0, 0, 0)) {
			if (size == smallest_group) {
				if (qe < lowest_qe) {
					lowest_qe = qe;
				}
			} else if (size < smallest_group) {
				smallest_group = size;
				lowest_qe = qe;
			}
			//}

			return;
		} else if (sum > limit || index >= weight_count) {
			return;
		}

		picked[index] = true;
		recurse_groups(index + 1, sum + weights[index]);
		picked[index] = false;
		recurse_groups(index + 1, sum);
	}

	recurse_groups(0, 0);

	long ans1 = lowest_qe;

	smallest_group = 1 << 30;
	lowest_qe = 1 << 30;

	limit = weight_sum / 4;
	//depth_limit = 2;

	recurse_groups(0, 0);

	long ans2 = lowest_qe;

	sprintf(input, "%ld, %ld", ans1, ans2);

    return input;
}
