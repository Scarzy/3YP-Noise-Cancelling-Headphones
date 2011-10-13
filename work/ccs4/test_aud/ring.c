#include "ring.h"
#include "dsk6713.h"
#include "dsk6713_led.h"
#include "dsk6713_dip.h"

#define A_SIZE 500

void main()
{
//	ringbuf a;//, b;
	int i = 0;
	Int32 a[A_SIZE];
	
	//DSK6713_init();
	//DSK6713_LED_init();
	//DSK6713_DIP_init();
	
	for(i = 0; i < A_SIZE; i++)
	{
		a[i] = 0;
	}
	DSK6713_LED_on(3);
//	init_ring(&a);
//	init_ring(&b);
		
/*	DSK6713_LED_on(0);
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
//			inc_ring(&a);
		}
		else
		{
			DSK6713_LED_off(1);
//			dec_ring(&a);
		}
	}
}

void inc_ring(void * a)
{
	if(((ringbuf *)a)->pos == ((ringbuf *)a)->ring + ((ringbuf *)a)->size - 1)
		((ringbuf *)a)->pos = ((ringbuf *)a)->ring;
	else
		((ringbuf *)a)->pos++;
}

void dec_ring(void *a)
{
	if(((ringbuf *)a)->pos == ((ringbuf *)a)->ring)
		((ringbuf *)a)->pos = ((ringbuf *)a)->ring + ((ringbuf *)a)->size - 1;
	else
		((ringbuf *)a)->pos--;
}

void init_ring(void *a)
{
	int i = 0;
	((ringbuf *)a)->size = RING_SIZE;
	((ringbuf *)a)->pos = ((ringbuf *)a)->ring;
	do
	{
		*((ringbuf *)a)->pos = 0;
		inc_ring(a);
		i++;
	}while( ((ringbuf *)a)->pos != ((ringbuf *)a)->ring );
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