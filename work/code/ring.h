#ifndef RING_H_
#define RING_H_

#define RING_SIZE 150

#include <tistdtypes.h>

typedef struct {
	Int32 * pos;
	Int32 size;
	Int32 ring[RING_SIZE];
} ringbuf;

void wave(void);

void init_ring(void *a);

void inc_ring(void *a);
void dec_ring(void *a);

#endif /*RING_H_*/
