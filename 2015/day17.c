#include "stdio.h"
#include "string.h"

int day_17_cmp(const void* a, const void* b) {
	return -(*(int*)a - *(int*)b);
}

char* solve_day_17(char* input) {

    int containers[30];
    int container_count = 0;

    char* tok = strtok(input, "\n");

    while (tok != NULL) {

        containers[container_count++] = atoi(tok);

        tok = strtok(NULL, "\n");
    }

    qsort(containers, container_count, sizeof(int), day_17_cmp);

    int combinations1 = 0;
    int combinations2 = 0;
    int min_containers = container_count;

    void test_combinations(int eggnog, int cur_containers, int index) {
        if (eggnog == 0) {
            combinations1++;

            if (cur_containers < min_containers) {
                min_containers = cur_containers;
                combinations2 = 1;
            } else if (cur_containers == min_containers) {
                combinations2++;
            }

            return;
        }

        if (eggnog < 0 || index == container_count) {
            return;
        }

        test_combinations(eggnog - containers[index], cur_containers + 1, index + 1);
        test_combinations(eggnog, cur_containers, index + 1);
    }

    test_combinations(150, 0, 0);

    sprintf(input, "%d, %d", combinations1, combinations2);

    return input;
}
