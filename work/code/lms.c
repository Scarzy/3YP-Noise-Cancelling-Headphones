#include "lms.h"

void init_taps(double * taps, int taplength)
{
	int i;
	for(i = 0; i < taplength; i++)
	{
		taps[i] = 0;
	}
}

void build_tap(void * ring, int16_t * ptrin, double * err, double * tap, int taplength, double * norm)
{
	int16_t * ptr = ptrin;
	int i;
	for(i = taplength - 1; i >= 0; i--)
	{
		tap[i] = LEAK_FACTOR * tap[i] + (MU_VALUE * *ptr * *err / *norm);
		dec_ring(ring, &ptr);
	}
}

void apply_tap(void * ring, int16_t * ptrin, double * tap, int tap_length, int16_t * out, double * normout, int16_t * desin, double * err)
{
	int16_t * ptr = ptrin;
	int16_t sum = 0;
	double normsum;
	int i;
	for(i = tap_length - 1; i >= 0; i--)
	{
		sum += tap[i] * *ptr;
		normsum += (*ptr * *ptr);
		dec_ring(ring, &ptr);
	}
	*out = sum;
	*normout = normsum;
	*err = *desin - *out;
}

