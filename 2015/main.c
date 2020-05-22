#include "stdio.h"
#include "time.h"

#include "day01.c"
#include "day02.c"
#include "day03.c"
#include "day04.c"
#include "day05.c"
#include "day06.c"
#include "day07.c"
#include "day08.c"
#include "day09.c"
#include "day10.c"
#include "day11.c"
#include "day12.c"
#include "day13.c"
#include "day14.c"
#include "day15.c"
#include "day16.c"
#include "day17.c"
#include "day18.c"
#include "day19.c"
#include "day20.c"
#include "day21.c"
#include "day22.c"
#include "day23.c"
#include "day24.c"
#include "day25.c"

char* (*solve_functions[])(char*) = {
	solve_day_01,
	solve_day_02,
	solve_day_03,
	solve_day_04,
	solve_day_05,
	solve_day_06,
	solve_day_07,
	solve_day_08,
	solve_day_09,
	solve_day_10,
	solve_day_11,
	solve_day_12,
	solve_day_13,
	solve_day_14,
	solve_day_15,
	solve_day_16,
	solve_day_17,
	solve_day_18,
	solve_day_19,
	solve_day_20,
	solve_day_21,
	solve_day_22,
	solve_day_23,
	solve_day_24,
	solve_day_25,
};

int main() {

	printf("\n");

	const int BUF_SIZE = 100000;

	char buf[BUF_SIZE];
	for (int i = 0; i < 25; i++) {
		int day = i + 1;

		char file_name[13];
		sprintf(file_name, "input/%02d.txt", day);
		FILE *input_file = fopen(file_name, "r");

		int read_bytes = 0;
		while (1) {
			int cur = fread(buf + read_bytes, 1, sizeof(buf), input_file);
			if (cur == 0) {
				break;
			}

			read_bytes += cur;
		}

		memset(buf + read_bytes, 0, BUF_SIZE - read_bytes);

		clock_t st = clock();
		char *result = (solve_functions[i])(buf);
		double duration = (double)(clock() - st) / CLOCKS_PER_SEC * 1000;

		if (result[0] != '\0') {
			printf("Day %2d: %8.3fms - %s\n", day, duration, result);
			fflush(stdout);
		}
	}

	printf("\n");

	return 0;
}
