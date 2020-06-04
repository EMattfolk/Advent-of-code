#include "stdio.h"
#include "string.h"

char* solve_day_25(char* input) {
	const char *delim = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,\n ";

	int row = atoi(strtok(input, delim));
	int col = atoi(strtok(NULL, delim));

	long powmod(long n, int e, long m) {
		int res = 1;
		while (e) {
			if (e & 1) {
				res = (res * n) % m;
			}
			n = (n * n) % m;
			e /= 2;
		}

		return res;
	}

	int prow = row + col - 1;
	int exp = prow * (prow + 1) / 2 - row;

	long code = 20151125;
	long mod = 33554393;
	int e = 252533;

	int ans = (code * powmod(e, exp, mod) ) % mod;

	sprintf(input, "%d", ans);

    return input;
}
