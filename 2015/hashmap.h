#pragma once

#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

static const float HASHMAP_RESIZE_THRESHOLD = 0.8f;

typedef struct node {
	void *key;
	void *value;
	uint64_t hash;
	struct node *next;
} node;

typedef struct {
	int key_size;
	int value_size;

	size_t size;
	size_t capacity;

	void *node_data;
	node *nodes;
	node **lists;
} hashmap;

hashmap hashmap_new(int key_size, int value_size);
node** hashmap_lookup(hashmap *hash_map, void* key, uint64_t hash);
void hashmap_put(hashmap *hash_map, void* key, void* value, uint64_t hash);
void* hashmap_get(hashmap *hash_map, void* key, uint64_t hash);
bool hashmap_contains(hashmap *hash_map, void* key, uint64_t hash);
void hashmap_resize(hashmap *hash_map, size_t capacity);
void hashmap_clear(hashmap *hash_map);
void hashmap_destroy(hashmap *hash_map);

#include "hashmap.c"
