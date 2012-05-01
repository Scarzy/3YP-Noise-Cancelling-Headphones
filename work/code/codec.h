#ifndef CODEC_H_
#define CODEC_H_

#include <stdint.h>

#define AIC23_CODEC_ID 0

void codecSetup(void);
void getData(int32_t * ptr);
void sendData(int32_t * ptr);
void codec_reg_set(uint16_t num, uint16_t val);
void codec_reset(void);
void codec_config(void);

int DSK6713_DIP_get(int a);
void DSK6713_LED_on(int a);
void DSK6713_LED_off(int a);

#endif /* CODEC_H_ */
