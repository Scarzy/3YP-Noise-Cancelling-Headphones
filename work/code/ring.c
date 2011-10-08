#include "ring.h"

void inc_ring(void * a)
{
	if(((ringbuf *)a)->pos == ((ringbuf *)a)->ring + ((ringbuf *)a)->size - 1)
		((ringbuf *)a)->pos = ((ringbuf *)a)->ring;
	else
		((ringbuf *)a)->pos++;
}

void dec_ring(void *a)
{
	if(((ringbuf *)a)->pos == ((ringbuf *)a)->ring)
		((ringbuf *)a)->pos = ((ringbuf *)a)->ring + ((ringbuf *)a)->size - 1;
	else
		((ringbuf *)a)->pos--;
}

void init_ring(void *a)
{
	int i = 0;
	((ringbuf *)a)->size = RING_SIZE;
	((ringbuf *)a)->pos = ((ringbuf *)a)->ring;
	do
	{
		*((ringbuf *)a)->pos = 0;
		inc_ring(a);
		i++;
	}while( ((ringbuf *)a)->pos != ((ringbuf *)a)->ring );
}

