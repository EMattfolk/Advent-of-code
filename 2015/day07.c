#include "stdio.h"
#include "string.h"
#include "stdint.h"

typedef struct wire {

	struct wire* left;
	struct wire* right;

	uint16_t value;
	bool has_value;

	void (*evaluate)(struct wire*);

} wire;

void not(wire *self) {
	if (self->left->has_value) {
		self->value = ~self->left->value;
		self->has_value = true;
	}
}

void forward(wire *self) {
	if (self->left->has_value) {
		self->value = self->left->value;
		self->has_value = true;
	}
}

void and(wire *self) {
	if (self->left->has_value && self->right->has_value) {
		self->value = self->left->value & self->right->value;
		self->has_value = true;
	}
}

void or(wire *self) {
	if (self->left->has_value && self->right->has_value) {
		self->value = self->left->value | self->right->value;
		self->has_value = true;
	}
}

void lshift(wire *self) {
	if (self->left->has_value && self->right->has_value) {
		self->value = self->left->value << self->right->value;
		self->has_value = true;
	}
}

void rshift(wire *self) {
	if (self->left->has_value && self->right->has_value) {
		self->value = self->left->value >> self->right->value;
		self->has_value = true;
	}
}

void constant(wire *self) {
	self->has_value = true;
}

char* solve_day_07(char* input) {

	wire wires[26 * 27];
	memset(wires, 0, sizeof(wires));
	wire const_wires[26 * 26];
	memset(const_wires, 0, sizeof(const_wires));
	int const_wire_count = 0;

	char* next() {
		char *a = strtok(NULL, " \n");
		//printf("Extracted: %s\n", a);
		return a;
	}

	int indexof(char* w) {
		if (w[1] == '\0') {
			return w[0] - 'a';
		}
		return w[1] - 'a' + 26 * (w[0] - 'a' + 1);
	}

	wire* to_wireptr(char* tok) {
		if (tok[0] >= '0' && tok[0] <= '9') {
			wire wre;
			wre.value = atoi(tok);
			wre.has_value = true;
			wre.evaluate = constant;
			const_wires[const_wire_count] = wre;

			return const_wires + const_wire_count++;
		} else {
			return wires + indexof(tok);
		}
	}

	char *tok = strtok(input, " \n");

	while (tok != NULL) {

		char *tokens[5];
		tokens[0] = tok;

		int size = 0;
		while (tokens[size++][0] != '-') {
			tokens[size] = next();
		}
		tokens[size++] = next();

		wire *wre = wires + indexof(tokens[size-1]);

		wre->value = 0;
		wre->has_value = false;
		wre->evaluate = NULL;

		if (size == 3) {
			wre->left = to_wireptr(tokens[0]);
			wre->right = NULL;
			wre->evaluate = forward;
		} else if (size == 4) {
			wre->left = to_wireptr(tokens[1]);
			wre->right = NULL;
			wre->evaluate = not;
		} else if (size == 5) {
			wre->left = to_wireptr(tokens[0]);
			wre->right = to_wireptr(tokens[2]);
			if (tokens[1][0] == 'A') {
				wre->evaluate = and;
			} else if (tokens[1][0] == 'O') {
				wre->evaluate = or;
			} else if (tokens[1][0] == 'L') {
				wre->evaluate = lshift;
			} else if (tokens[1][0] == 'R') {
				wre->evaluate = rshift;
			} else {
				printf("big error\n");
				fflush(stdout);
			}

		} else {
			printf("big error\n");
			fflush(stdout);
		}

		tok = next();
	}

	while (!wires[indexof("a")].has_value) {
		for (int i = 0; i < 26 * 27; i++) {
			if (wires[i].evaluate != NULL) {
				(wires[i].evaluate)(wires + i);
			}
		}
	}
	
	int ans1 = wires[indexof("a")].value;

	wires[indexof("b")].left->value = 3176;

	for (int i = 0; i < 26 * 27; i++) {
		wires[i].has_value = false;
	}

	while (!wires[indexof("a")].has_value) {
		for (int i = 0; i < 26 * 27; i++) {
			if (wires[i].evaluate != NULL) {
				(wires[i].evaluate)(wires + i);
			}
		}
	}

	int ans2 = wires[indexof("a")].value;

	sprintf(input, "%d, %d", ans1, ans2);

    return input;
}
