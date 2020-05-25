#include "stdio.h"
#include "string.h"
#include "hashmap.h"
#include "utils.h"

char* solve_day_13(char* input) {

	int dist_table[10][10];

	inline char* next() {
		return strtok(NULL, ". \n");
	}

	hashmap name_to_index = HASHMAP(string, int);

	char *tok = strtok(input, ". \n");
	int people_count = 0;

	while (tok != NULL) {

		char *person_a = tok;
		next();
		char *sign = next();
		int value = atoi(next()) * (sign[0] == 'g' ? 1 : -1);
		next();
		next();
		next();
		next();
		next();
		next();
		char *person_b = next();

		string persons[2] = { to_string(person_a), to_string(person_b) };
		for (int i = 0; i < 2; i++) {
			string *person = &persons[i];
			if (!hashmap_contains(&name_to_index, person, djb2(person))) {
				hashmap_put(&name_to_index, person, &people_count, djb2(person));
				people_count++;
			}
		}

		int ai = *(int*)hashmap_get(&name_to_index, persons + 0, djb2(persons + 0));
		int bi = *(int*)hashmap_get(&name_to_index, persons + 1, djb2(persons + 1));

		dist_table[ai][bi] = value;

		tok = next();
	}

	hashmap_destroy(&name_to_index);

	int best1 = 0;
	int best2 = 0;
	string permutation;
	for (int i = 0; i < people_count; i++) {
		sprintf(permutation.chars + i, "%d", i);
	}

	void swap(char* a, char* b) {
		char temp = *a;
		*a = *b;
		*b = temp;
	}

	void run_permutations(char *per, int l, int r) {
		if (l == r) {
			int happiness = 0;
			int min_change = 1 << 30;
			for (int i = 0; i < r; i++) {
				int from = per[i] - '0';
				int to = per[(i+1) % r] - '0';
				int change = dist_table[from][to] + dist_table[to][from];
				happiness += change;
				min_change = change < min_change ? change : min_change;
			}

			best1 = happiness > best1 ? happiness : best1;
			best2 = happiness - min_change > best2 ? happiness - min_change : best2;
		}

		for (int i = l; i < r; i++) {
			swap(per + l, per + i);
			run_permutations(per, l + 1, r);
			swap(per + l, per + i);
		}
	}

	run_permutations(permutation.chars, 0, people_count);

	sprintf(input, "%d, %d", best1, best2);
	
    return input;
}
