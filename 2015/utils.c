#include "utils.h"

string to_string(const char *s) {
	string str;
	memset(str.chars, 0, LOCAL_STRING_SIZE * sizeof(char));

	bool success = false;
	for (int i = 0; i < LOCAL_STRING_SIZE; i++) {
		str.chars[i] = s[i];
		if (s[i] == '\0') {
			success = true;
			break;
		}
	}

	if (!success) {
		printf("String construction failed for string '%s': not enough buffer space\n", s);
		fflush(stdout);
	}

	return str;
}

long_string to_long_string(const char *s) {
	long_string str;
	memset(str.chars, 0, LONG_LOCAL_STRING_SIZE * sizeof(char));

	bool success = false;
	for (int i = 0; i < LONG_LOCAL_STRING_SIZE; i++) {
		str.chars[i] = s[i];
		if (s[i] == '\0') {
			success = true;
			break;
		}
	}

	if (!success) {
		printf("String construction failed for string '%s': not enough buffer space\n", s);
		fflush(stdout);
	}

	return str;
}

uint64_t djb2(const char *str) {
	uint64_t hash = 5381;
	int c;

	char *it = (char*)str;
	while ((c = *it++)) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}
