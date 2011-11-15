#ifndef __SIG_PROC_H_
#define __SIG_PROC_H_

#include <math.h>

#define CROSS_CORR_MAX_DELAY 200

void cancel(void * ring1, int16_t * ptr1in, void * ring2, int16_t *ptr2in, void * res, int16_t * ptrres);
void crosscorr(int16_t * arr1, int16_t * arr2, double * res, int length, int maxdel);
int dpeak(double * arr, int length);
double mean(int16_t * arr, int length);

#endif /* __SIG_PROC_H_ */
