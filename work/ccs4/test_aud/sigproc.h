#ifndef __SIG_PROC_H_
#define __SIG_PROC_H_

#include <math.h>
#include "ring.h"

#define CROSS_CORR_MAX_DELAY 200

void cancel(void * ring1, int16_t * ptr1in, uint16_t update1, void * ring2, int16_t *ptr2in, uint16_t update2, void * res, int16_t * ptrres);
void crosscorr(void * ring1, int16_t * ptr1in, uint16_t update1, void * ring2, int16_t * ptr2in, uint16_t update2, double * res, int16_t length, int16_t maxdel, int * shift);

#endif /* __SIG_PROC_H_ */
