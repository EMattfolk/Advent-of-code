#include "stdio.h"
#include "string.h"
#include "hashmap.h"

char* solve_day_03(char* input) {
	hashmap visited = HASHMAP(point, int);
	point santa = { 0, 0 };
	point robo_santa = { 0, 0 };
	int init_presents = 1;

	hashmap_put(&visited, &santa, &init_presents, point_hash(&santa));

	int solve(point *robo_santa) {
		char* it = input;
		char c;
		point *pos = robo_santa;
		while ((c = *it++)) {
			pos = pos == robo_santa ? &santa : robo_santa;
			pos->x += (c == '>' ? 1 : (c == '<' ? -1 : 0));
			pos->y += (c == '^' ? 1 : (c == 'v' ? -1 : 0));

			if (hashmap_contains(&visited, pos, point_hash(pos))) {
				(*(int*)hashmap_get(&visited, pos, point_hash(pos)))++;
			} else {
				hashmap_put(&visited, pos, &init_presents, point_hash(pos));
			}
		}

		return visited.size;
	}

	size_t ans1 = solve(&santa);

	hashmap_clear(&visited);
	santa.x = 0;
	santa.y = 0;

	size_t ans2 = solve(&robo_santa);

	sprintf(input, "%ld, %ld", ans1, ans2);

	hashmap_destroy(&visited);

    return input;
}
