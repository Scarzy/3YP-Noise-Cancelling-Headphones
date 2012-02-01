#include "sigproc.h"

double cc[2*CROSS_CORR_MAX_DELAY+1];

double ccmeansum1, ccmeansum2;

void cancel(void * ring1, int16_t * ptr1in, void * ring2, int16_t * ptr2in, void * res, int16_t * ptrres)
{
	int shift,i;
	int16_t * ptr1 = ptr1in;
	int16_t * ptr2 = ptr2in;
	crosscorr(ring1, ptr1, ring2, ptr2, cc, ((ringbuf *)ring1)->size, CROSS_CORR_MAX_DELAY, &shift);
	if(shift < 0)
	{
		for(i = 0; i < shift; i++)
		{
			inc_ring(ring2, &ptr2);
		}
	}
	for(i = 0; i < ((ringbuf *)ring1)->size; i++)
	{
		*ptrres = ((i - shift) <= 0) ? *ptr1 : *ptr1 - *ptr2 ;
		inc_ring(ring1, &ptr1);
		inc_ring(res,&ptrres);
		if(!(i < shift))
			inc_ring(ring2, &ptr2);
	}
}

void crosscorr(void * ring1, int16_t * ptr1in, void * ring2, int16_t * ptr2in, double * res, int16_t length, int16_t maxdel, int * shift)
{
	int del, i, j;
	double mean1, mean2;
	int16_t * ptr1 = ptr1in;
	int16_t * ptr2 = ptr2in;
	double s, sqrttmp0, sqrttmp1;
	double sum1 = 0, sum2 = 0;
	
	int pos = 0;
	double max = 0;
	
	ccmeansum1 += *ptr1;
	inc_ring(ring1, &ptr1);
	ccmeansum1 -= *ptr1;
	
	ccmeansum2 += *ptr2;
	inc_ring(ring2, &ptr2);
	ccmeansum2 -= *ptr2;
	
	mean1 = ccmeansum1 / ((ringbuf *)ring1)->size;
	mean2 = ccmeansum2 / ((ringbuf *)ring2)->size;
	
	for(i = 0; i < length; i++)
	{
		sum1 += ((*ptr1 - mean1) * (*ptr1 - mean1));
		sum2 += ((*ptr2 - mean2) * (*ptr2 - mean2));
		inc_ring(ring1, &ptr1);
		inc_ring(ring2, &ptr2);
	}
	
	sqrttmp0 = sum1 * sum2;
	sqrttmp1 = fabs(sqrttmp0);
	s = sqrt(sqrttmp1);
	
	for(del = -maxdel; del <= maxdel; del++)
	{
		double num = 0;
		ptr1 = ptr1in;
		ptr2 = ptr2in;
		for(i = 0; i < length; i++)
		{
			j = i + del;
			if(!( (j < 0) || (j >= length) ))
			{
				num += ((*ptr1 - mean1) * (*ptr2 - mean2));
			}
			inc_ring(ring1, &ptr1);
			inc_ring(ring2, &ptr2);
		}
			
		res[del + maxdel] = num / s;
		
		if(abs(arr[i]) > max)
		{
			max = abs(arr[i]);
			pos = i;
		}
	}
	shift = pos;
}

