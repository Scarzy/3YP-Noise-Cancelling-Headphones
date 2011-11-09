#ifndef RING_H_
#define RING_H_

#include <stdint.h>
#include <tistdtypes.h>

#define DATA_RING 0
#define PROC_RING 1

typedef struct {
	int32_t * ring0;
	int32_t * ring1;
	int32_t size;
	int8_t dataring;
} ringbuf;

void init_ring(void *ring, int32_t * arr, int size);
void init_ring_ptr(void *ring, int32_t ** ptr);

void inc_ring(void * ring, int32_t ** ptr);
void dec_ring(void * ring, int32_t ** ptr);

void switch_ring(void * ring);

#endif /*RING_H_*/
