#include "lms.h"

void build_tap(void * ring, int16_t * ptrin, double * err, double * tap, int taplength, double * norm)
{
	int16_t * ptr = ptrin;
	int i;
	for(i = taplength - 1; i >= 0; i--)
	{
		tap[i] = LEAK_FACTOR * tap[i] + (MU_VALUE * noiin[i] * *err / *norm);
		dec_ring(ring, &ptr);
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

void gen_error(int16_t * desin, int16_t * estin, double * err)
{
	*err = *desin - *errin;
}

void calc_norm(void ring, int16_t * ptrin, double * normout)
{
	int16_t * ptr = ptrin;
	double sum = 0;
	int i;
	for(i = tap_length - 1; i >= 0; i--)
	{
		sum += (*ptr * *ptr);
		dec_ring(ring, &ptr);
	}
	*normout = sum;
}

