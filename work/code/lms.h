#ifndef __LMS_H_
#define __LMS_H_

#include <stdint.h>

#define TAP_LENGTH 50

#define MU_VALUE 0.0005
#define LEAK_FACTOR 1

#define NORM_MIN 1

void init_taps(double * taps, int taplength);
void build_tap(void * ring, int16_t * ptrin, double * err, double * tap, int taplength, double * norm);
void apply_tap(void * ring, int16_t * ptrin, double * tap, int tap_length, int16_t * out, double * norm, int16_t * desin, double * err);

#endif	/* __LMS_H_ */
