#include "stdio.h"
#include "string.h"
#include "hashmap.h"
#include "utils.h"

char* solve_day_09(char* input) {

	int dist_table[10][10];

	inline char* next() {
		return strtok(NULL, " \n");
	}

	hashmap name_to_index = HASHMAP(string, int);

	char *tok = strtok(input, " \n");
	int city_number = 0;

	while (tok != NULL) {

		char *city_a = tok;
		next();
		char *city_b = next();
		next();
		int dist = atoi(next());

		string cities[2] = { to_string(city_a), to_string(city_b) };
		for (int i = 0; i < 2; i++) {
			string *city = &cities[i];
			if (!hashmap_contains(&name_to_index, city, djb2(city->chars))) {
				hashmap_put(&name_to_index, city, &city_number, djb2(city->chars));
				city_number++;
			}
		}

		int ai = *(int*)hashmap_get(&name_to_index, cities + 0, djb2(cities[0].chars));
		int bi = *(int*)hashmap_get(&name_to_index, cities + 1, djb2(cities[1].chars));

		dist_table[ai][bi] = dist;
		dist_table[bi][ai] = dist;

		tok = next();
	}

	//for (int i = 0; i < name_to_index.size; i++) {
	//	node n = name_to_index.nodes[i];
	//	printf("%s: %d\n", (char*)n.key, *(int*)n.value);
	//}
	
	hashmap_destroy(&name_to_index);

	int shortest = 1 << 30;
	int longest = 0;
	string permutation;
	for (int i = 0; i < city_number; i++) {
		sprintf(permutation.chars + i, "%d", i);
	}

	void swap(char* a, char* b) {
		char temp = *a;
		*a = *b;
		*b = temp;
	}

	void run_permutations(char *per, int l, int r) {
		if (l == r) {
			int dist = 0;
			for (int i = 0; i < r - 1; i++) {
				int from = per[i] - '0';
				int to = per[i+1] - '0';
				dist += dist_table[from][to];
			}

			shortest = dist < shortest ? dist : shortest;
			longest = dist > longest ? dist : longest;
		}

		for (int i = l; i < r; i++) {
			swap(per + l, per + i);
			run_permutations(per, l + 1, r);
			swap(per + l, per + i);
		}
	}

	run_permutations(permutation.chars, 0, city_number);

	sprintf(input, "%d, %d", shortest, longest);
	
    return input;
}
