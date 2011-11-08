#include "ring.h"

void inc_ring(void * ring, int32_t ** ptr)
{
	if(*ptr == ((ringbuf *)ring)->ring + ((ringbuf *)ring)->size - 1)
		*ptr = ((ringbuf *)ring)->ring;
	else
		*ptr = *ptr + 1;
}

void dec_ring(void * ring, int32_t ** ptr)
{
	if(*ptr == ((ringbuf *)ring)->ring)
		*ptr = ((ringbuf *)ring)->ring + ((ringbuf *)ring)->size - 1;
	else
		*ptr = *ptr - 1;
}

void init_ring(void *ring, int32_t * arr, int size)
{
	int i = 0;
	int32_t * ptr;
	((ringbuf *)ring)->ring = arr;
	((ringbuf *)ring)->size = size;
	ptr = ((ringbuf *)ring)->ring;
	do
	{
		*ptr = 0;
		inc_ring(ring, &ptr);
		i++;
	}while( ptr != ((ringbuf *)ring)->ring );
}

void init_ring_ptr(void *ring, int32_t ** ptr)
{
	*ptr = ((ringbuf *)ring)->ring;
}
 
