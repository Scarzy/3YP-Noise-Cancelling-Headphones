#include "lms.h"

void build_tap(double * noiin, int noisize, double * err, double * tap, int taplength)
{
	int i;
	for(i = 0; i < taplength; i++)
	{
		tap[i] = LEAK_FACTOR * tap[i] - MU_VALUE * noiin[i] * err;
	}
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

void gen_error(int16_t * desin, int16_t * estin, int16_t * err)
{
	*err = *desin + *errin;
}

