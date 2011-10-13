#ifndef CODEC_H_
#define CODEC_H_

#include <csl.h>
#include <dsk6713_aic23.h>

struct codec_data{
	Int16 right;
	Int16 left;
};

//DSK6713_AIC23_CodecHandle codec;

volatile struct codec_data data_in;
volatile struct codec_data data_out;


#endif /*CODEC_H_*/
