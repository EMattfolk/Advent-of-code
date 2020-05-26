#include "stdio.h"
#include "string.h"
#include "hashmap.h"

char* solve_day_16(char* input) {

    const char* keys[] = {
        "children",
        "cats",
        "samoyeds",
        "pomeranians",
        "akitas",
        "vizslas",
        "goldfish",
        "trees",
        "cars",
        "perfumes",
    };

    int values[] = { 3, 7, 2, 3, 0, 0, 5, 3, 2, 1 };

    hashmap data = HASHMAP(string, int);

    for (int i = 0; i < 10; i++) {
        string key = to_string(keys[i]);
        int value = values[i];

        hashmap_put(&data, &key, &value, djb2(&key));
    }

    inline char* next() {
        return strtok(NULL, ":, \n");
    }

    bool cmp1(string *key, int value) {
        return !hashmap_contains(&data, key, djb2(key)) ||
            *(int*)hashmap_get(&data, key, djb2(key)) == value;
    }

    bool cmp2(string *key, int value) {
        if (key->chars[2] == 't' || key->chars[0] == 't') {
            return !hashmap_contains(&data, key, djb2(key)) ||
                *(int*)hashmap_get(&data, key, djb2(key)) < value;
        } else if ((key->chars[0] == 'p' && key->chars[1] == 'o') || key->chars[3] == 'd') {
            return !hashmap_contains(&data, key, djb2(key)) ||
                *(int*)hashmap_get(&data, key, djb2(key)) > value;
        }

        return !hashmap_contains(&data, key, djb2(key)) ||
            *(int*)hashmap_get(&data, key, djb2(key)) == value;
    }

    int sue1 = 0;
    int sue2 = 0;

    char* tok = strtok(input, ":, \n");
    while (tok != NULL) {

        bool is_right1 = true;
        bool is_right2 = true;
        int sue = atoi(next());

        string key = to_string(next());
        int value = atoi(next());

        is_right1 &= cmp1(&key, value);
        is_right2 &= cmp2(&key, value);

        key = to_string(next());
        value = atoi(next());

        is_right1 &= cmp1(&key, value);
        is_right2 &= cmp2(&key, value);

        key = to_string(next());
        value = atoi(next());

        is_right1 &= cmp1(&key, value);
        is_right2 &= cmp2(&key, value);

        if (is_right1) {
            sue1 = sue;
        }

        if (is_right2) {
            sue2 = sue;
        }

        tok = next();
    }

    hashmap_destroy(&data);

    sprintf(input, "%d, %d", sue1, sue2);

    return input;
}
