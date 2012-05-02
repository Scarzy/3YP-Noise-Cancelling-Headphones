#include "ring.h"
#include "lms.h"
#include <stdint.h>
#include <dsk6713.h>
#include <dsk6713_aic23.h>
#include "dsk6713_led.h"
#include "dsk6713_dip.h"
#include "codec.h"
#include "sigproc.h"

#define BUF_SIZE 10000

#define WAVE_DEL 4096

int16_t lbufin[BUF_SIZE];
int16_t rbufin[BUF_SIZE];
int16_t lbufout[BUF_SIZE];
int16_t rbufout[BUF_SIZE];

extern DSK6713_AIC23_CodecHandle codec;

ringbuf lringin;
ringbuf rringin;
ringbuf lringout;
ringbuf rringout;
int16_t * lptrin;
int16_t * rptrin;
int16_t * lptrout;
int16_t * rptrout;
int16_t * lptrcpyi;
int16_t * rptrcpyi;
int16_t * lptrcpyo;
int16_t * rptrcpyo;

double lmstaps[TAP_LENGTH];

int wave_count = 0;
int16_t wave_del = 0;

void test(void);
void wave(void);

void main()
{
	init_ring(&lringin, lbufin, BUF_SIZE);
	init_ring(&rringin, rbufin, BUF_SIZE);
	init_ring_ptr(&lringin, &lptrin);
	init_ring_ptr(&rringin, &rptrin);
	codecSetup();
	init_taps(lmstaps,TAP_LENGTH);
	test();
}

void test()
{
	double lmsnorm = NORM_MIN, lmserr = 0;
	while(1)
	{
		int16_t lmsout;
		int32_t in, out;
		if(!DSK6713_DIP_get(0))
		{
			if(wave_del)
				DSK6713_LED_on(1);
			else
				DSK6713_LED_off(1);
			wave_del = 1 - wave_del;
		}
		if(!DSK6713_DIP_get(1))
		{
//			printf("looping\n");
			getData(&in);
			*lptrin = ((in & 0xFFFF0000) >> 16);
			*rptrin = (in & 0x0000FFFF);
			
			apply_tap(&lringin, lptrin, lmstaps, TAP_LENGTH, &lmsout, &lmsnorm, rptrin, &lmserr);
			
			out = (0x00000000 | ((0x0000FFFF & (int16_t)floor(lmserr)) << 16) | ((int16_t)floor(lmserr) & 0x0000FFFF));
			sendData(&out);
			
			inc_ring(&lringin, &lptrin);
			inc_ring(&rringin, &rptrin);
		}
		else
		{
			getData(&in);
			in &= 0x0000FFFF;
			*rptrin = in;
			inc_ring(&rringin,&rptrin);
			sendData(&in);
		}
	}
}

void wave()
{
	if(wave_del++ != WAVE_DEL)
	{
		return;
	}
	wave_del = 0;
	
	switch(wave_count++)
	{
		case 0: 	DSK6713_LED_on(0);
        			DSK6713_LED_off(1);
        			DSK6713_LED_off(2);
        			DSK6713_LED_off(3);
        			break;
		case 1: 	DSK6713_LED_off(0);
        			DSK6713_LED_on(1);
        			DSK6713_LED_off(2);
        			DSK6713_LED_off(3);
        			break;
		case 2: 	DSK6713_LED_off(0);
        			DSK6713_LED_off(1);
        			DSK6713_LED_on(2);
        			DSK6713_LED_off(3);
        			break;
		case 3: 	DSK6713_LED_off(0);
        			DSK6713_LED_off(1);
        			DSK6713_LED_off(2);
        			DSK6713_LED_on(3);
        			break;
		case 4: 	DSK6713_LED_off(0);
        			DSK6713_LED_off(1);
        			DSK6713_LED_on(2);
        			DSK6713_LED_off(3);
        			break;
		case 5: 	DSK6713_LED_off(0);
        			DSK6713_LED_on(1);
        			DSK6713_LED_off(2);
        			DSK6713_LED_off(3);
        			wave_count = 0;
        			break;
		default: 	DSK6713_LED_off(0);
        			DSK6713_LED_off(1);
        			DSK6713_LED_off(2);
        			DSK6713_LED_off(3);
        			wave_count = 0;
        			break;
	}
}
