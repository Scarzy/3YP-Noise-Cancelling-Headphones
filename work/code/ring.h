#ifndef RING_H_
#define RING_H_

#include <stdint.h>

typedef struct {
	int16_t * ring;
	int16_t size;
} ringbuf;

void init_ring(void *ring, int16_t * arr, int size);
void init_ring_ptr(void *ring, int16_t ** ptr);

void inc_ring(void * ring, int16_t ** ptr);
void dec_ring(void * ring, int16_t ** ptr);

#endif /*RING_H_*/
