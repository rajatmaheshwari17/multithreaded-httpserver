#ifndef CACHER_H
#define CACHER_H

#include <stdbool.h>

typedef enum {
    FIFO,
    LRU,
    CLOCK
} cache_policy_t;

typedef struct {
    char *key;
    char *data;
    long size;
} cache_item_t;

typedef struct {
    cache_item_t *items;
    int capacity;
    int count;
    cache_policy_t policy;
} cache_t;

cache_t *cache_create(int capacity, cache_policy_t policy);
void cache_destroy(cache_t *cache);
bool cache_lookup(cache_t *cache, const char *key);
void cache_insert(cache_t *cache, const char *key);
void cache_evict(cache_t *cache);
void cache_update(cache_t *cache, const char *key, const char *content, long content_length);
void cache_retrieve_data(cache_t *cache, const char *key, char **buffer, long *size);

#endif