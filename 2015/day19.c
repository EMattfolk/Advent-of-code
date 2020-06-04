#include "stdio.h"
#include "string.h"
#include "hashmap.h"
#include "utils.h"

char* solve_day_19(char* input) {

	int dummy;

	typedef struct list {
		char *data[10];
		int size;
	} list;

	list new_list() {
		list l;
		memset(&l, 0, sizeof(list));
		return l;
	}

	hashmap substitutions = HASHMAP(string, list);
	hashmap reverse_substitutions = HASHMAP(string, string);

	inline char* next() {
		return strtok(NULL, " =>\n");
	}

	char *tok = strtok(input, " =>\n");

	long_string molecule;

	while (true) {
		char *pattern = tok;
		char *sub = next();

		if (sub == NULL) {
			molecule = to_long_string(pattern);
			break;
		}

		string p = to_string(pattern);
		string s = to_string(sub);

		if (!hashmap_contains(&substitutions, &p, djb2(p.chars))) {
			list l = new_list();
			hashmap_put(&substitutions, &p, &l, djb2(p.chars));
		}

		list *sublist = (list*)hashmap_get(&substitutions, &p, djb2(p.chars));
		sublist->data[sublist->size++] = sub;

		hashmap_put(&reverse_substitutions, &s, &p, djb2(s.chars));

		tok = next();
	}

	hashmap unique = HASHMAP(long_string, int);

	void generate(long_string molecule, hashmap *unique) {
		for (int i = 0; i < substitutions.size; i++) {
			string *pattern = (string*)substitutions.nodes[i].key;
			list *sublist = (list*)substitutions.nodes[i].value;

			int pattern_size = strlen(pattern->chars);

			char *it = strstr(molecule.chars, pattern->chars);
			while (it != NULL) {

				// Construct new molecules from the pattern at position it
				// and the subsititutions in sublist.
				// Then put them in unique.

				for (int j = 0; j < sublist->size; j++) {

					char *sub = sublist->data[j];
					long_string new_molecule = to_long_string("");

					int molecule_index = 0;
					int new_molecule_index = 0;
					while (molecule.chars[molecule_index] != '\0') {
						if (molecule.chars + molecule_index == it) {
							molecule_index += pattern_size;
							char c;
							while ((c = *(sub++))) {
								new_molecule.chars[new_molecule_index++] = c;
							}
						} else {
							new_molecule.chars[new_molecule_index++] =
								molecule.chars[molecule_index++];
						}
					}
					if (strlen(new_molecule.chars) < LONG_LOCAL_STRING_SIZE - 10) {
						hashmap_put(unique, &new_molecule, &dummy, djb2(new_molecule.chars));
					}
				}

				it = strstr(it + 1, pattern->chars);
			}
		}
	}

	generate(molecule, &unique);

	int ans1 = unique.size;

	hashmap_destroy(&substitutions);
	hashmap_destroy(&unique);

	/* All substitutions are of the form
	 *
	 * e -> XX
	 * X -> XX | X(X,X) | X(X,X,X)
	 *
	 * where
	 *
	 * Rn = '(', Ar = ')', Y = ','
	 *
	 * All other tokens are X
	 *
	 * So the amount of productions needed to create some string is:
	 *     #X - #, - 1
	 *
	 * The -1 is because the first production yields 2 X
	 */

	int ans2 = -1;

	bool is_lower(char c) {
		return c >= 'a' && c <= 'z';
	}

	char *it = molecule.chars;
	while (*it != '\0') {
		int tok_size = 1 + is_lower(it[1]);

		if (tok_size == 1 && !strncmp(it, "Y", 1)) {
			ans2--;
		}
		else if (strncmp(it, "Ar", 2) && strncmp(it, "Rn", 2)) {
			ans2++;
		}

		it += tok_size;
	}

	sprintf(input, "%d, %d", ans1, ans2);

    return input;
}
