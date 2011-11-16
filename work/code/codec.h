#ifndef CODEC_H_
#define CODEC_H_

#include <csl.h>
#include <dsk6713.h>
#include <dsk6713_aic23.h>
#include <stdint.h>

#define AIC23_CODEC_ID 0

void codecSetup(void);
void getData(uint32_t * ptr);
void sendData(uint32_t * ptr);
void codec_reg_set(uint16_t num, uint16_t val);
void codec_reset(void);

#endif /* CODEC_H_ */
