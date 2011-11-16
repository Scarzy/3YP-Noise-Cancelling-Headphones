#include "sigproc.h"

void cancel(void * ring1, int16_t * ptr1in, void * ring2, int16_t * ptr2in, void * res, int16_t * ptrres)
{
	int shift,i;
	double cc[2*CROSS_CORR_MAX_DELAY+1];
	int16_t * ptr1 = ptr1in;
	int16_t * ptr2 = ptr2in;
	crosscorr(ring1, ptr1, ring2, ptr2, cc, ((ringbuf *)ring1)->size, CROSS_CORR_MAX_DELAY);
	shift = dpeak(cc, ((ringbuf *)ring1)->size);
	if(shift < 0)
	{
		for(i = 0; i < shift; i++)
		{
			inc_ring(&ring2, &ptr2);
		}
	}
	for(i = 0; i < ((ringbuf *)ring1)->size; i++)
	{
		*ptrres = ((i - shift) <= 0) ? *ptr1 : *ptr1 - *ptr2 ;
		inc_ring(&ring1, &ptr1);
		if(!(i < shift))
			inc_ring(&ring2, &ptr2);
	}
}

void crosscorr(void * ring1, int16_t * ptr1in, void * ring2, int16_t * ptr2in, double * res, int length, int maxdel)
{
	int del, i, j;
	double mean1, mean2;
	int16_t * ptr1 = ptr1in;
	int16_t * ptr2 = ptr2in;
	mean1 = mean(ring1, ptr1);
	mean2 = mean(ring2, ptr2);
	
	for(del = -maxdel; del < maxdel; del++)
	{
		int sum1, sum2;
		double s;
		int num = 0;
		ptr1 = ptr1in;
		ptr2 = ptr2in;
		for(i = 0; i < length; i++)
		{
			j = i + del;
			if(!( (j < 0) || (j >= length) ))
			{
				num += ((*ptr1 - mean1) * (*ptr2 - mean2));
			}
			inc_ring(&ring1, &ptr1);
			inc_ring(&ring2, &ptr2);
		}
		
		ptr1 = ptr1in;
		ptr2 = ptr2in;
		sum1 = 0;
		sum2 = 0;
		for(i = 0; i < length; i++)
		{
			sum1 += ((*ptr1 - mean1) * (*ptr1 - mean1));
			sum2 += ((*ptr2 - mean2) * (*ptr2 - mean2));
			inc_ring(&ring1, &ptr1);
			inc_ring(&ring2, &ptr2);
		}
		s = sqrt(sum1 * sum2);
		res[del + maxdel] = num / s;
	}
}

int dpeak(double * arr, int length)
{
	double max = 0;
	int i, pos = 0;
	for(i = 0; i < length; i++)
	{
		if(abs(arr[i]) > max)
		{
			max = abs(arr[i]);
			pos = i;
		}
	}
	return pos;
}

double mean(void * ring, int16_t * ptrin)
{
	int i;
	double mean = 0;
	int16_t * ptr = ptrin;
	for(i = 0; i < ((ringbuf *)ring)->size; i++)
	{
		mean += *ptr;
		inc_ring(&ring, &ptr);
	}
	return mean / ((ringbuf *)ring)->size;
}

