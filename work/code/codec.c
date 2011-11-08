#include "codec.h"

McBSP_Handle mcbspControlHandle;
McBSP_Handle mcbspDataHandle;
DSK6713_AIC23_CodecHandle codec;

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
	codec = DSK6713_AIC23_openCodec(AIC23_CODEC_ID, &aic23_config);
}
