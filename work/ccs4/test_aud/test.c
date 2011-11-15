#include "ring.h"
#include <stdint.h>
#include <dsk6713.h>
#include <dsk6713_aic23.h>
#include "dsk6713_led.h"
#include "dsk6713_dip.h"
#include "codec.h"

#define BUF_SIZE 20000
#define WAVE_DEL 4096

int32_t buf[BUF_SIZE];

extern DSK6713_AIC23_CodecHandle codec;

uint32_t a_val_in;
int16_t r_val_out, l_val_out;

ringbuf ring;
int32_t * ptr;

int wave_count = 0;
int16_t wave_del = 0;

void test(void);
void wave(void);

void main()
{
	init_ring(&ring, buf, BUF_SIZE);
	init_ring_ptr(&ring, &ptr);
	codecSetup();
	test();
}

void test()
{
	while(1)
	{
		if(!DSK6713_DIP_get(0))
			wave();
		
		if(!DSK6713_DIP_get(1) && !DSK6713_DIP_get(2))
		{
			DSK6713_AIC23_read(codec,ptr);
//			getData(ptr);
		}
		
		if(!DSK6713_DIP_get(1))
		{
			int32_t a;// = *ptr;
//			int16_t l = a;
			if(!DSK6713_DIP_get(3))
				a = *ptr & 0x0000FFFF;
			else
				a = *ptr & 0xFFFF0000;
//			int16_t r = a<<16;
			while(!DSK6713_AIC23_write(codec,a));
//			while(!DSK6713_AIC23_write(codec,r));
		}
		inc_ring(&ring, &ptr);
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
