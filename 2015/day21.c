#include "stdio.h"
#include "string.h"
#include "utils.h"

char* solve_day_21(char* input) {

	inline char* next() {
		return strtok(NULL, " :\n");
	}

	strtok(input, " :\n");
	next();

	int boss_hp = atoi(next());

	next();

	int boss_damage = atoi(next());

	next();

	int boss_armor = atoi(next());

	typedef struct equipment {
		int cost;
		int damage;
		int armor;
	} equipment;

	equipment weapons[5] = {
		{  8, 4, 0 },
		{ 10, 5, 0 },
		{ 25, 6, 0 },
		{ 40, 7, 0 },
		{ 74, 8, 0 },
	};

	equipment armors[6] = {
		{   0, 0, 0 },
		{  13, 0, 1 },
		{  31, 0, 2 },
		{  53, 0, 3 },
		{  75, 0, 4 },
		{ 102, 0, 5 },
	};

	equipment rings[8] = {
		{   0, 0, 0 },
		{   0, 0, 0 },
		{  25, 1, 0 },
		{  50, 2, 0 },
		{ 100, 3, 0 },
		{  20, 0, 1 },
		{  40, 0, 2 },
		{  80, 0, 3 },
	};

	int min_cost = 1 << 30;
	int max_cost = 0;

	int hp = 100;
	for (int w = 0; w < 5; w++) {
		for (int a = 0; a < 6; a++) {
			for (int r1 = 0; r1 < 8; r1++) {
				for (int r2 = r1 + 1; r2 < 8; r2++) {
					int cost = weapons[w].cost +
						armors[a].cost +
						rings[r1].cost + rings[r2].cost;
					int damage = weapons[w].damage +
						armors[a].damage +
						rings[r1].damage + rings[r2].damage;
					int armor = weapons[w].armor +
						armors[a].armor +
						rings[r1].armor + rings[r2].armor;

					int actual_damage = MAX(1, damage - boss_armor);
					int actual_boss_damage = MAX(1, boss_damage - armor);

					int turns = boss_hp / actual_damage + (boss_hp % actual_damage != 0);
					int boss_turns = hp / actual_boss_damage + (hp % actual_boss_damage != 0);

					if (turns <= boss_turns) {
						min_cost = MIN(cost, min_cost);
					} else {
						max_cost = MAX(cost, max_cost);
					}
				}
			}
		}
	}

	sprintf(input, "%d, %d", min_cost, max_cost);

    return input;
}
