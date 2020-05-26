#pragma once

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define LOCAL_STRING_SIZE 20

typedef struct local_string {
	char chars[LOCAL_STRING_SIZE];
} string;

string to_string(const char *s);
uint64_t djb2(const string *str);

#include "utils.c"
