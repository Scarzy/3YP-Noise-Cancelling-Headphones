#include "ring.h"

void inc_ring(void * a, int32_t * ptr)
{
	if(ptr == ((ringbuf *)a)->ring + ((ringbuf *)a)->size - 1)
		ptr = ((ringbuf *)a)->ring;
	else
		ptr++;
}

void dec_ring(void * a, int32_t * ptr)
{
	if(ptr == ((ringbuf *)a)->ring)
		ptr = ((ringbuf *)a)->ring + ((ringbuf *)a)->size - 1;
	else
		ptr--;
}

void init_ring(void *a)
{
	int i = 0;
	int32_t * ptr;
	((ringbuf *)a)->size = RING_SIZE;
	ptr = ((ringbuf *)a)->ring;
	do
	{
		*ptr = 0;
		inc_ring(a, ptr);
		i++;
	}while( ptr != ((ringbuf *)a)->ring );
}

void init_ring_ptr(void *a, int32_t * ptr)
{
	ptr = ((ringbuf *)a)->ring;
}
 
