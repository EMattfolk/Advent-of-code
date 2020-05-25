#include "stdio.h"
#include "string.h"
#include "utils.h"

char* solve_day_15(char* input) {

	typedef struct ingredient {
		int capacity;
		int durability;
		int flavor;
		int texture;
		int calories;
	} ingredient;

	inline char* next() {
		return strtok(NULL, ": ,\n");
	}
		
	char *tok = strtok(input, ": ,\n");

	ingredient ingredients[4];
	int ingredient_count = 0;

	while (tok != NULL) {
		ingredient ing;

		next();
		ing.capacity = atoi(next());
		next();
		ing.durability = atoi(next());
		next();
		ing.flavor = atoi(next());
		next();
		ing.texture = atoi(next());
		next();
		ing.calories = atoi(next());

		ingredients[ingredient_count++] = ing;

		tok = next();
	}

	int score(int a, int b, int c, int d, int *cal) {
		int capacity = 0, durability = 0, flavor = 0, texture = 0, calories = 0;
		int weights[4] = {a, b, c, d};

		for (int i = 0; i < 4; i++) {
			capacity += weights[i] * ingredients[i].capacity;
			durability += weights[i] * ingredients[i].durability;
			flavor += weights[i] * ingredients[i].flavor;
			texture += weights[i] * ingredients[i].texture;
			calories += weights[i] * ingredients[i].calories;
		}

		*cal = calories;

		if (capacity < 0 || durability < 0 || flavor < 0 || texture < 0) {
			return 0;
		}

		return capacity * durability * flavor * texture;
	}

	int best_score = 0;
	int best_500_cal = 0;
	for (int a = 0; a <= 100; a++) {
		for (int b = 0; b <= 100 - a; b++) {
			for (int c = 0; c <= 100 - a - b; c++) {
				int d = 100 - a - b - c;
				int calories = 0;
				int s = score(a, b, c, d, &calories);

				best_score = MAX(best_score, s);
				if (calories == 500) {
					best_500_cal = MAX(best_500_cal, s);
				}
			}
		}
	}

	sprintf(input, "%d, %d", best_score, best_500_cal);

    return input;
}
