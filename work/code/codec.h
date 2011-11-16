#ifndef CODEC_H_
#define CODEC_H_

#include <csl.h>
#include <dsk6713.h>
#include <dsk6713_aic23.h>
#include <stdint.h>

#define AIC23_CODEC_ID 0

void codecSetup(void);
void getData(int32_t * ptr);

#endif /* CODEC_H_ */
