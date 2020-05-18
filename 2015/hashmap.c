#include "hashmap.h"

#define HASHMAP(K, V) hashmap_new(sizeof(K), sizeof(V))

hashmap hashmap_new(int key_size, int value_size) {
	hashmap hash_map;
	hash_map.key_size = key_size;
	hash_map.value_size = value_size;
	hash_map.size = 0;
	hash_map.capacity = 32;
	hash_map.node_data = calloc(hash_map.capacity, hash_map.key_size + hash_map.value_size);
	hash_map.nodes = calloc(hash_map.capacity, sizeof(node));
	hash_map.lists = calloc(hash_map.capacity, sizeof(node*));

	return hash_map;
}

node** hashmap_lookup(hashmap *hash_map, void* key, uint64_t hash) {
	size_t index = hash % hash_map->capacity;
	node **list = hash_map->lists + index;

	while (1) {
		if (*list == NULL) {
			return list;
		} else if ((*list)->hash == hash) {
			bool same = true;
			char *node_key = (*list)->key;
			for (int i = 0; i < hash_map->key_size; i++) {
				if (((char*)key)[i] != node_key[i]) {
					same = false;
					break;
				}
			}
			
			if (same) {
				return list;
				//memcpy(node_data, data, hash_map->value_size);
				//break;
			}
		}

		list = &(*list)->next;
	}

	return NULL;
}

void hashmap_put(hashmap *hash_map, void* key, void* value, uint64_t hash) {

	if (hash_map->size * 1.0 / hash_map->capacity >= HASHMAP_RESIZE_THRESHOLD) {
		hashmap_resize(hash_map, hash_map->capacity * 2);
	}
		
	node** location = hashmap_lookup(hash_map, key, hash);
	if (*location == NULL) {
		node *n = hash_map->nodes + hash_map->size;
		n->key = hash_map->node_data +
			(hash_map->key_size + hash_map->value_size) * hash_map->size;
		n->value = n->key + hash_map->key_size;
		n->hash = hash;
		n->next = NULL;

		memcpy(n->key, key, hash_map->key_size);
		memcpy(n->value, value, hash_map->value_size);

		*location = n;
		hash_map->size++;
	} else {
		memcpy((*location)->value, value, hash_map->value_size);
	}
}

void* hashmap_get(hashmap *hash_map, void* key, uint64_t hash) {
	return (*hashmap_lookup(hash_map, key, hash))->value;
}

bool hashmap_contains(hashmap *hash_map, void* key, uint64_t hash) {
	return *hashmap_lookup(hash_map, key, hash) != NULL;
}

void hashmap_resize(hashmap *hash_map, size_t capacity) {
	if (capacity <= hash_map->capacity) {
		return;
	}

	hashmap old = *hash_map;

	hash_map->size = 0;
	hash_map->capacity = capacity;
	hash_map->node_data = calloc(hash_map->capacity, hash_map->key_size + hash_map->value_size);
	hash_map->nodes = calloc(hash_map->capacity, sizeof(node));
	hash_map->lists = calloc(hash_map->capacity, sizeof(node*));
	
	// Insert old values into new hashmap
	for (int i = 0; i < old.size; i++) {
		node entry = old.nodes[i];
		hashmap_put(hash_map, entry.key, entry.value, entry.hash);
	}

	hashmap_destroy(&old);
}

void hashmap_clear(hashmap *hash_map) {
	hash_map->size = 0;
	for (int i = 0; i < hash_map->capacity; i++) {
		hash_map->lists[i] = NULL;
	}
}

void hashmap_destroy(hashmap *hash_map) {
	free(hash_map->node_data);
	free(hash_map->nodes);
	free(hash_map->lists);
}

typedef struct point {
	int x;
	int y;
} point;

uint64_t point_hash(point* p) {
	uint64_t hash = 23;
	hash = hash * 33 + p->x;
	return hash * 33 + p->y;
}

/*
int main() {
#include "stdio.h"
	hashmap h = HASHMAP(point, int);
	point p = { 0, 0 };

	int lim = 20000;

	for (int i = 0; i < lim; i++) {
		p.x = i;
		hashmap_put(&h, &p, &i, point_hash(&p));
	}

	for (int i = 0; i < lim; i++) {
		p.x = i;
		int *value = hashmap_get(&h, &p, point_hash(&p));
		bool contains = hashmap_contains(&h, &p, point_hash(&p));
		printf("(%d, %d): %d - contains: %d\n", p.x, p.y, *value, contains);
	}

	hashmap_destroy(&h);

	return 0;
}
*/
