#pragma once

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define LOCAL_STRING_SIZE 20
#define LONG_LOCAL_STRING_SIZE 500

typedef struct local_string {
	char chars[LOCAL_STRING_SIZE];
} string;

typedef struct long_local_string {
	char chars[LONG_LOCAL_STRING_SIZE];
} long_string;

string to_string(const char *s);
long_string to_long_string(const char *s);
uint64_t djb2(const char *str);

#include "utils.c"
