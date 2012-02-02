#include "lms.h"

void build_tap(double * cc, int ccsize, double * ac, int acsize, double * tap, int taplength)
{
	
}

void apply_tap(void * ring, int16_t * ptrin, double * tap, int tap_length, int16_t * out)
{
	int16_t * ptr = ptrin;
	int16_t sum = 0;
	int i;
	for(i = tap_length - 1; i >= 0; i--)
	{
		sum += tap[i] * *ptr;
		dec_ring(ring, &ptr);
	}
	*out = sum;
}

