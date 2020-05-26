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

uint64_t djb2(const string *str) {
	uint64_t hash = 5381;
	int c;

	char *it = (char*)str;
	while ((c = *it++)) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}
