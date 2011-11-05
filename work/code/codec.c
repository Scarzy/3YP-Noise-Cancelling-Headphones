#include "codec.h"

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

void codecSetup()
{
	codec = DSK6713_AIC23_openCodec(AIC23_CODEC_ID, &aic23_config);
}
