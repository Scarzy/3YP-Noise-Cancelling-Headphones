#include "lms.h"

void init_taps(double * taps, int taplength)
{
	int i;
	for(i = 0; i < taplength; i++)
	{
		taps[i] = 0;
	}
}

void apply_tap(void * ring, int16_t * ptrin, double * tap, int tap_length, int16_t * out, double * normout, int16_t * desin, double * err)
{
	int16_t * ptr = ptrin;
	int16_t sum = 0, val;
	double normsum = NORM_MIN;
	int i;
	for(i = tap_length - 1; i >= 0; i--)
	{
		val = *ptr;
		tap[i] = LEAK_FACTOR * tap[i] + (MU_VALUE * val * *err / *normout);
		//if(tap[i] > TAP_MAG_MAX)
	//		tap[i] = TAP_MAG_MAX;
	//	else if(tap[i] < -TAP_MAG_MAX)
	//		 tap[i] = -TAP_MAG_MAX;
		sum += tap[i] * val;
		normsum += (val * val);
		dec_ring(ring, &ptr);
	}
	*out = sum;
	*normout = normsum;
	*err = *desin - sum;
}

