#pragma once

#define LOCAL_STRING_SIZE 20

typedef struct local_string {
	char chars[LOCAL_STRING_SIZE];
} string;

string to_string(char *s);
uint64_t djb2(string *str);

#include "utils.c"
