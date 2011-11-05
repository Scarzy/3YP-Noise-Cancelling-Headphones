#include "codec.h"

DSK6713_AIC23_CodecHandle codec;

void codecSetup()
{
	codec = DSK6713_AIC23_openCodec(AIC23_CODEC_ID, &aic23_config);
}
