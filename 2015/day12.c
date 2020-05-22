#include "stdio.h"
#include "string.h"
#include "utils.h"

void parse_dict(char **json);
void parse_list(char **json);
bool parse_string(char **json);
void parse_int(char **json);
void parse_json(char **json);

int day_12_ans1 = 0;
int day_12_ans2 = 0;

void parse_dict(char **json) {
	char *text = *json;
	text++;

	int init_ans2 = day_12_ans2;
	bool has_red = false;

	while (*text != '}') {
		parse_string(&text);
		text++;
		if (*text == '"') {
			has_red |= parse_string(&text);
		} else {
			parse_json(&text);
		}
		if (*text == ',') {
			text++;
		}
	}

	if (has_red) {
		day_12_ans2 = init_ans2;
	}

	*json = text + 1;
}

void parse_list(char **json) {
	char *text = *json;
	text++;

	while (*text != ']') {
		parse_json(&text);
		if (*text == ',') {
			text++;
		}
	}

	*json = text + 1;
}

bool parse_string(char **json) {
	char *text = *json;
	text++;

	char *begin = text;

	while (*text++ != '"');

	char *end = text - 1;

	const char *red = "red";
	bool is_red = true;

	for (int i = 0; i < 3; i++) {
		if (begin + i == end) {
			is_red = false;
			break;
		}

		is_red &= begin[i] == red[i];
	}

	*json = text;

	return is_red;
}

void parse_int(char **json) {
	char *text = *json;

	char *end;
	int value = strtol(text, &end, 10);
	day_12_ans1 += value;
	day_12_ans2 += value;
	text = end;

	*json = text;
}

void parse_json(char **json) {
	char *text = *json;

	char first = *text;
	switch (first) {
		case '{':
			parse_dict(&text);
			break;
		case '[':
			parse_list(&text);
			break;
		case '"':
			parse_string(&text);
			break;
		default:
			parse_int(&text);
			break;
	}

	*json = text;
}

char* solve_day_12(char* input) {

	parse_json(&input);

	sprintf(input, "%d, %d", day_12_ans1, day_12_ans2);

    return input;
}
