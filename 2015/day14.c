#include "stdio.h"
#include "string.h"
#include "utils.h"

char* solve_day_14(char* input) {

	typedef struct reindeer {
		int speed;
		int speed_dur;
		int rest_dur;
		int points;
	} reindeer;

	reindeer reindeers[10];
	int reindeer_count = 0;

	int integrate(reindeer *r, int time) {
		int cycle_dur = r->speed_dur + r->rest_dur;
		int full_cycles = time / cycle_dur;
		int remainder = time - full_cycles * cycle_dur;

		return (full_cycles * r->speed_dur + MIN(remainder, r->speed_dur)) * r->speed;
	}

	inline char* next() {
		return strtok(NULL, " ,.\n");
	}

	int duration = 2503;

	char *tok = strtok(input, " ,.\n");

	while (tok != NULL) {
		next();
		next();
		int speed = atoi(next());
		next();
		next();
		int speed_dur = atoi(next());
		next();
		next();
		next();
		next();
		next();
		next();
		int rest_dur = atoi(next());
		next();

		reindeers[reindeer_count++] = (reindeer) {speed, speed_dur, rest_dur, 0};

		tok = next();
	}

	for (int t = 1; t <= duration; t++) {
		int farthest = 0;
		for (int i = 0; i < reindeer_count; i++) {
			farthest = MAX(farthest, integrate(reindeers + i, t));
		}
		for (int i = 0; i < reindeer_count; i++) {
			if (integrate(reindeers + i, t) == farthest) {
				reindeers[i].points++;
			}
		}
	}

	int best_dist = 0;
	int best_points = 0;
	for (int i = 0; i < reindeer_count; i++) {
		best_dist = MAX(best_dist, integrate(reindeers + i, duration));
		best_points = MAX(best_points, reindeers[i].points);
	}

	sprintf(input, "%d, %d", best_dist, best_points);

    return input;
}
