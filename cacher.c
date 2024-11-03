
#include "cacher.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>

cache_t *cache_create(int capacity, cache_policy_t policy) {
    cache_t *cache = malloc(sizeof(cache_t));
    if (!cache) return NULL;

    cache->items = malloc(sizeof(cache_item_t) * capacity);
    if (!cache->items) {
        free(cache);
        return NULL;
    }

    cache->capacity = capacity;
    cache->count = 0;
    cache->policy = policy;
    return cache;
}

void cache_destroy(cache_t *cache) {
    if (cache) {
        for (int i = 0; i < cache->count; i++) {
            free(cache->items[i].key);
        }
        free(cache->items);
        free(cache);
    }
}

bool cache_lookup(cache_t *cache, const char *key) {
    int i = 0;
    while (i < cache->count) {
        if (strcmp(cache->items[i].key, key) == 0) {
            log_message(LOG_INFO, "Cache hit for key '%s'", key);
            return true;
        }
        i++;
    }
    log_message(LOG_INFO, "Cache miss for key '%s'", key);
    return false;
}

void cache_insert(cache_t *cache, const char *key) {
    if (cache->count >= cache->capacity) {
        cache_evict(cache);
        log_message(LOG_INFO, "Cache evict called due to full capacity");
    }
    cache->items[cache->count].key = strdup(key);
    cache->count++;
    log_message(LOG_INFO, "Inserted key '%s' into cache", key);
}


void cache_evict(cache_t *cache) {
    if (cache->count > 0) {
        log_message(LOG_INFO, "Evicting key '%s' from cache", cache->items[0].key);
        free(cache->items[0].key);
        memmove(cache->items, cache->items + 1, sizeof(cache_item_t) * (cache->count - 1));
        cache->count--;
    }
}


void cache_retrieve_data(cache_t *cache, const char *key, char **buffer, long *size) {
    int i = 0;
    while (i < cache->count) {
        if (strcmp(cache->items[i].key, key) == 0) {
            *size = cache->items[i].size;
            *buffer = malloc(*size);
            memcpy(*buffer, cache->items[i].data, *size);
            return;
        }
        i++;
    }
    *buffer = NULL;
    *size = 0;
}

void cache_update(cache_t *cache, const char *key, const char *content, long content_length) {
    int i = 0;
    while (i < cache->count) {
        if (strcmp(cache->items[i].key, key) == 0) {
            free(cache->items[i].data);
            cache->items[i].data = malloc(content_length);
            memcpy(cache->items[i].data, content, content_length);
            cache->items[i].size = content_length;
            return;
        }
        i++;
    }
    log_message(LOG_INFO, "Updated key '%s' in cache", key);
}