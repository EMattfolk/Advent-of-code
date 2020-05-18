#include "stdio.h"
#include "string.h"
#include "stdbool.h"

char* solve_day_05(char* input) {

	bool is_nice1(char* word) {
		int vowels = 0;
		bool twice = false;
		bool illegal = false;

		char *it = word;
		char cur;
		char last = '\0';

		while ((cur = *it++) != '\0') {
			vowels += cur == 'a';
			vowels += cur == 'e';
			vowels += cur == 'i';
			vowels += cur == 'o';
			vowels += cur == 'u';

			twice |= cur == last;

			illegal |= (last == 'a' && cur == 'b') ||
				(last == 'c' && cur == 'd') ||
				(last == 'p' && cur == 'q') ||
				(last == 'x' && cur == 'y');

			last = cur;
		}
		
		return vowels >= 3 && twice && !illegal;
	}

	bool is_nice2(char* word) {

		bool overlap = false;
		bool repeat = false;

		int len = strlen(word);

		for (int i = 0; i < len - 1; i++) {
			char a = word[i], b = word[i+1];
			for (int j = i + 2; j < len - 1; j++) {
				char x = word[j], y = word[j+1];
				overlap |= a == x && b == y;
			}
		}

		for (int i = 0; i < len - 2; i++) {
			repeat |= word[i] == word[i+2];
		}

		return overlap && repeat;
	}

	int nice1 = 0;
	int nice2 = 0;

	char *tok = strtok(input, "\n");

	while (tok != NULL) {

		nice1 += is_nice1(tok);
		nice2 += is_nice2(tok);

		tok = strtok(NULL, "\n");
	}

    sprintf(input, "%d, %d", nice1, nice2);

    return input;
}
