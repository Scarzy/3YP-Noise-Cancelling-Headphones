#ifndef RING_H_
#define RING_H_

#define RING_SIZE 150

#include <stdint.h>
#include <tistdtypes.h>

typedef struct {
	int32_t * ring;
	int32_t size;
} ringbuf;

void init_ring(void *a);
void init_ring_ptr(void *a, int32_t * ptr);

void inc_ring(void * a, int32_t * ptr);
void dec_ring(void * a, int32_t * ptr);

#endif /*RING_H_*/
