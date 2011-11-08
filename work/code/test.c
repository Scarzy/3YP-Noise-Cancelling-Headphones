#include "ring.h"
#include <stdint.h>
#include "dsk6713.h"
#include "dsk6713_led.h"
#include "dsk6713_dip.h"
#include "codec.h"

#define BUF_SIZE 10000

volatile int32_t buf_l[BUF_SIZE];
volatile int32_t buf_r[BUF_SIZE];

void test(void);
void wave(void);

void main()
{
	ringbuf ring_l, ring_r;
	int32_t * ptr;
	init_ring(&ring_l, buf_l, BUF_SIZE);
	init_ring(&ring_r, buf_r, BUF_SIZE);
	init_ring_ptr(&ring_l, &ptr);
	codecSetup();
	test();
}

void test()
{
	while(1)
	{
		if(!DSK6713_DIP_get(0))
			wave();
		
		if(!DSK6713_DIP_get(1))
		{
			DSK6713_LED_on(1);
			inc_ring(&ring_a, &ptr);
		}
		else
		{
			DSK6713_LED_off(1);
			dec_ring(&ring_a, &ptr);
		}
	}
}

void wave()
{
	int count = 0;
	while(1)
    {
        switch(count++)
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
        				count = 0;
        				break;
        	default: 	DSK6713_LED_off(0);
        				DSK6713_LED_off(1);
        				DSK6713_LED_off(2);
        				DSK6713_LED_off(3);
        				count = 0;
        				break;
        }
	DSK6713_waitusec(100000);
	
	if(DSK6713_DIP_get(0))
	{
		DSK6713_LED_off(0);
        	DSK6713_LED_off(1);
        	DSK6713_LED_off(2);
        	DSK6713_LED_off(3);
        	return;			
	}
    }
}
