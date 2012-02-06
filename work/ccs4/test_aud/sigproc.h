#ifndef __SIG_PROC_H_
#define __SIG_PROC_H_

#include <math.h>
#include "dsk6713_led.h"
#include "ring.h"

#define CROSS_CORR_MAX_DELAY 20

void cancel(void * ring1, int16_t * ptr1in, void * ring2, int16_t *ptr2in, void * res, int16_t * ptrres);
void crosscorr(void * ring1, int16_t * ptr1in, void * ring2, int16_t * ptr2in, double * res, int16_t length, int16_t maxdel);
int dpeak(double * arr, int length);
double mean(void * ring, int16_t * ptrin);

#endif /* __SIG_PROC_H_ */
