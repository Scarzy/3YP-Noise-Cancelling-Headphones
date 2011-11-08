#include <stdbool.h>
#include "codec.h"

McBSP_Handle mcbspControlHandle;
McBSP_Handle mcbspDataHandle;
DSK6713_AIC23_CodecHandle codec;
	
DSK6713_AIC23_Config aic23_config = {
	0x0017,	//Left Line In Volume, No simultaneous update - unmuted - 0dB
	0x0017,	//Right Line In Volume, No simultaneous update - unmuted - 0dB
	0x01D9,	//Left Headphone Volume, No simultaneous update - zero cross - 0dB
	0x01D9,	//Right Headphone Volume, No simultaneous update - zero cross - 0dB
	0x0011,	//Analog Audio Path Control, Side tone disabled - DAC on - use unmuted Mic and boost it
	0x0000,	//Digital Audio Path Control, DAC unmuted - no Deemphasis - ADC high pass enabled
	0x0000,	//Power Down Control, CLK off
	0x0043,	//Digital Audio Format, Slave - no DAC swap - 16bit input - MSB first left aligned
	0x0081,	//Sample Rate Control, ADC 48KHz - DAC 48KHz
	0x0001	//Digital Interface Activation, Active
};

volatile extern int32_t buf_l*, buf_r*;

#pragma vector=YKNOW_THAT_VECTOR
__interrupt void newSample()
{
	
}

#pragma vector=YKNOW_THAT_OTHER_VECTOR
__interrupt void sendSample()
{
	
}

bool mcbspSetup()
{
	mcbspControlHandle = MCBSP_open(MCBSP_DEV0, MCBSP_OPEN_RESET);
	mcbspDataHandle = MCBSP_open(MCBSP_DEV1, MCBSP_OPEN_RESET);
	if(mcbspControlHandle == INV || mcbspDataHandle == INV)
	{
		return false;
	}
	MCBSP_config(mcbspControlHandle, mcbsp_control_config);
	MCBSP_config(mcbspDataHandle, mcbsp_data_config);
	
}

void codecSetup()
{
	DSK6713_init();
	codec = DSK6713_AIC23_openCodec(AIC23_CODEC_ID, &aic23_config);
}
