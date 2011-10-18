#include "ring.h"
#include <stdint.h>
#include "dsk6713.h"
#include "dsk6713_led.h"
#include "dsk6713_dip.h"

#define A_SIZE 10

void wave(void);

void main()
{
	int32_t a[A_SIZE];
/*	int32_t i = 0;
	
	for(i = 0; i < A_SIZE; i++)
	{
		a[i] = 0;
	}
	
	while(1);*/
	
	ringbuf ring;
	int32_t * ptr;
	init_ring(&ring, a, A_SIZE);
	init_ring_ptr(&ring, &ptr);
/*	ringbuf a, b;
	
	init_ring(&a);
	init_ring(&b);
	
	DSK6713_init();
	DSK6713_LED_init();
	DSK6713_DIP_init();
	
	DSK6713_LED_on(0);
	DSK6713_LED_on(1);
	DSK6713_LED_on(2);
	DSK6713_LED_on(3);
	DSK6713_waitusec(100000);
	DSK6713_LED_off(0);
	DSK6713_LED_off(1);
	DSK6713_LED_off(2);
	DSK6713_LED_off(3);
	DSK6713_waitusec(100000);
	DSK6713_LED_on(0);
	DSK6713_LED_on(1);
	DSK6713_LED_on(2);
	DSK6713_LED_on(3);*/
	
	
	while(1)
	{
		if(!DSK6713_DIP_get(0))
			wave();
		
		if(!DSK6713_DIP_get(1))
		{
			DSK6713_LED_on(1);
			inc_ring(&ring, &ptr);
		}
		else
		{
			DSK6713_LED_off(1);
			dec_ring(&ring, &ptr);
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
