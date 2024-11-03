#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>

typedef struct queue {
    void **elements;
    int head;
    int tail;
    int maxSize;
    pthread_mutex_t lock;
} queue_t;

queue_t *queue_new(int size);
void queue_delete(queue_t **q);
void queue_push(queue_t *q, void *elem);
void queue_pop(queue_t *q, void **elem);

#endif