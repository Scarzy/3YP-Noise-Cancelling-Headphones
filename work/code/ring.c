#include "ring.h"

void inc_ring(void * ring, int32_t ** ptr, int8_t dataring)
{
	if((*ptr >= ((ringbuf *)ring)->ring1) ^ ((ringbuf *)ring)->dataring ^ dataring)
	{
		if(*ptr >= ((ringbuf *)ring)->ring1)
			*ptr = ((ringbuf *)ring)->ring0 + (*ptr - ((ringbuf *)ring)->ring1);
		else
			*ptr = ((ringbuf *)ring)->ring1 + (*ptr - ((ringbuf *)ring)->ring0);
	}
	
	if(!(((ringbuf *)ring)->dataring == DATA_RING ^ dataring == DATA_RING))
	{
		if(*ptr == ((ringbuf *)ring)->ring0 + ((ringbuf *)ring)->size - 1)
			*ptr = ((ringbuf *)ring)->ring0;
		else
			*ptr = *ptr + 1;
	}
	else
	{
		if(*ptr == ((ringbuf *)ring)->ring1 + ((ringbuf *)ring)->size - 1)
			*ptr = ((ringbuf *)ring)->ring1;
		else
			*ptr = *ptr + 1;
	}
}

void dec_ring(void * ring, int32_t ** ptr)
{
	if((*ptr >= ((ringbuf *)ring)->ring1) ^ ((ringbuf *)ring)->dataring ^ dataring)
	{
		if(*ptr >= ((ringbuf *)ring)->ring1)
			*ptr = ((ringbuf *)ring)->ring0 + (*ptr - ((ringbuf *)ring)->ring1);
		if(*ptr < ((ringbuf *)ring)->ring1)
			*ptr = ((ringbuf *)ring)->ring1 + (*ptr - ((ringbuf *)ring)->ring0);	
	}
	if(!(((ringbuf *)ring)->dataring == DATA_RING ^ dataring == DATA_RING))
	{
		if(*ptr == ((ringbuf *)ring)->ring0)
			*ptr = ((ringbuf *)ring)->ring0 + ((ringbuf *)ring)->size - 1;
		else
			*ptr = *ptr - 1;
	}
	else
	{
		if(*ptr == ((ringbuf *)ring)->ring1)
			*ptr = ((ringbuf *)ring)->ring1 + ((ringbuf *)ring)->size - 1;
		else
			*ptr = *ptr - 1;
	}
}

void init_ring(void *ring, int32_t * arr0, int32_t * arr1, int size)
{
	int i = 0;
	int32_t * ptr;
	((ringbuf *)ring)->dataring = DATA_RING;
	((ringbuf *)ring)->ring0 = arr0;
	((ringbuf *)ring)->ring1 = arr1;
	((ringbuf *)ring)->size = size;
	ptr = ((ringbuf *)ring)->ring0;
	do
	{
		*ptr = 0;
		inc_ring(ring, &ptr);
		i++;
	}while( ptr != ((ringbuf *)ring)->ring0 );
	ptr = ((ringbuf *)ring)->ring1;
	do
	{
		*ptr = 0;
		inc_ring(ring, &ptr);
		i++;
	}while( ptr != ((ringbuf *)ring)->ring1 );
}

void init_ring_ptr(void *ring, int32_t ** ptr, int8_t dataring)
{
	*ptr = (dataring == DATA_RING) ? ((ringbuf *)ring)->ring0 : ((ringbuf *)ring)->ring1;
}

void switch_ring(void * ring)
{
	((ringbuf *)ring)->dataring = 1 - ((ringbuf *)ring)->dataring;
}

