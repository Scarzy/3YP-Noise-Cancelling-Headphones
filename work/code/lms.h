#ifndef __LMS_H_
#define __LMS_H_

#include <stdint.h>

#define MU_VALUE 0.8

void build_tap(double * cc, int ccsize, double * ac, int acsize, double * tap, int taplength);
void apply_tap(void * ring, int16_t * ptrin, double * tap, int tap_length, int16_t * out);
void gen_error(int16_t * desin, int16_t * estin, int16_t * err);

#endif	/* __LMS_H_ */
