#ifndef __SIG_PROC_H_
#define __SIG_PROC_H_

#include <math.h>

#define CROSS_CORR_MAX_DELAY 200

void cancel(int16_t * arr1, int16_t * arr2, int16_t * res, int length);
void crosscorr(int16_t * arr1, int16_t * arr2, double * res, int length, int maxdel);
int dpeak(double * arr, int length);
double mean(int16_t * arr, int length);

#endif /* __SIG_PROC_H_ */
