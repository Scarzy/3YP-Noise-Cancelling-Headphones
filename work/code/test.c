#include "ring.h"
#include <stdint.h>
#include <dsk6713.h>
#include <dsk6713_aic23.h>
#include "dsk6713_led.h"
#include "dsk6713_dip.h"
#include "codec.h"

#define BUF_SIZE 10000

#define WAVE_DEL 4096

int16_t lbufin[BUF_SIZE];
int16_t rbufin[BUF_SIZE];
int16_t lbugout[BUF_SIZE];
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

int wave_count = 0;
int16_t wave_del = 0;

void test(void);
void wave(void);

void main()
{
	init_ring(&lringin, lbufin, BUF_SIZE);
	init_ring(&rringin, rbufin, BUF_SIZE);
	init_ring(&lringout, lbufout, BUF_SIZE);
	init_ring(&rringout, rbufout, BUF_SIZE);
	init_ring_ptr(&lringin, &lptrin);
	init_ring_ptr(&rringin, &rptrin);
	init_ring_ptr(&lringout, &lptrout);
	init_ring_ptr(&rringout, &rptrout);
	init_ring_ptr(&lringin, &lptrcpyi);
	init_ring_ptr(&rringin, &rptrcpyi);
	init_ring_ptr(&lringout, &lptrcpyo);
	init_ring_ptr(&rringout, &rptrcpyo);
	codecSetup();
	test();
}

void test()
{
	while(1)
	{
		uint32_t in, out;
		if(!DSK6713_DIP_get(0))
			wave();
		
		if(!DSK6713_DIP_get(1))
		{
			getData(&in);
			*lptrin = ((in & 0xFFFF0000) >> 16);
			*rptrin = (in & 0x0000FFFF);
			inc_ring(&lringin, &lptrin);
			inc_ring(&rringin, &rptrin);
		}
		
		if(!DSK6713_DIP_get(2))
		{
			*lptrcpyo = *lptrcpyi;
			*rptrcpyo = *rptrcpyi;
			inc_ring(&lringin, &lptrcpyi);
			inc_ring(&rringin, &lptrcpyi);
			inc_ring(&lringout, &lptrcpyo);
			inc_ring(&rringout, &lptrcpyo);
		}
		
		if(!DSK6713_DIP_get(3))
		{
			out = (0x00000000 | (*lptrout << 16) | *rptrout);
			sendData(&out);
			inc_ring(&lringout, &lptrout);
			inc_ring(&rringout, &rptrout);
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
