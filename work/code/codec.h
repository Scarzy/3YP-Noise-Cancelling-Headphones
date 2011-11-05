#include <dsk6713_aic23.h>

#define AIC23_CODEC_ID 0

DSK6713_AIC23_Config aic23_config = {
	0x017,	//Left Line In Volume, No simultaneous update - unmuted - 0dB
	0x017,	//Right Line In Volume, No simultaneous update - unmuted - 0dB
	0x089,	//Left Headphone Volume, No simultaneous update - zero cross - 0dB
	0x089,	//Right Headphone Volume, No simultaneous update - zero cross - 0dB
	0x015,	//Analog Audio Path Control, Side tone disabled - DAC on - use unmuted Mic and boost it
	0x000,	//Digital Audio Path Control, DAC unmuted - no Deemphasis - ADC high pass enabled
	0x040,	//Power Down Control, CLK off
	0x001,	//Digital Audio Format, Slave - no DAC swap - 16bit input - MSB first left aligned
	0x081,	//Sample Rate Control, ADC 48KHz - DAC 48KHz
	0x001	//Digital Interface Activation, Active
};

void codecSetup(void);

