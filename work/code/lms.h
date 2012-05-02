#ifndef __LMS_H_
#define __LMS_H_

#include <stdint.h>
#include "ring.h"

#define TAP_LENGTH 13

#define MU_VALUE 0.0005
#define LEAK_FACTOR 1

#define NORM_MIN 0.0000000000000002		//Minimum value for the normalising denominator, prevents divide by 0

void init_taps(double * taps, int taplength);
void apply_tap(void * ring, int16_t * ptrin, double * tap, int tap_length, int16_t * out, double * norm, int16_t * desin, double * err);

#endif	/* __LMS_H_ */
