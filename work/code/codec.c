#include "codec.h"
#include <dsk6713_led.h>

MCBSP_Handle mcbspControlHandle;
MCBSP_Handle mcbspDataHandle;
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
MCBSP_Config mcbsp_data_config = {
	//MCBSP_FMKS(REGISTER, PORTION, VALUE);
	
	//SPCR - Serial Port Control Register
	//	31-26	RESERVED
	//	25	FREE	If set then serial clocks run during emulation halt.
	//	24	SOFT	If set then current operation completes before clocks disabled, else they stop instantly. Only valid if FREE not set.
	//	23	FRST	Frame Sync generator reset. If set then frame sync signal generated, else signal not generated.
	//	22	GRST	Sample Rate generator reset. If set sample rate signal generated as set in SRGR.
	//	21-20	XINTM	Transmit Interupt (XINT) Enable.
	//				0	XINT driven by XRDY, end of word and end of frame
	//				1	XINT generated by end of block and end of frame
	//				2	XINT generated by new frame sync
	//				3	XINT generated by XSYNCERR
	//	19	XSYNCERR Transmit Sync Error. If set then error has been detected.
	//	18	XEMPTY	Transmit Shift Register Empty. If set then XSR is empty.			STATUS
	//	17	XRDY	Transmitter Ready. If set then transmitter ready for new data in DXR.		STATUS
	//	16	XRST	Transmitter Reset. If not set then transmitter disabled.
	//	15	DLB	Digital Loop Back enable. If set then digital loop back enabled.
	//	14-13	RJUST	Receive sign extension and justify.
	//				0	RZF - Right justify, 0 fill
	//				1	RSE - Right justify, sign extend
	//				2	LZF - Left justify, 0 fill
	//				3	RESERVED
	//	12-11	CLKSTP	Clock Stop mode.
	//				0	Clock stop disabled
	//				1	RESERVED
	//				2	In SPI mode, clock starts with delay. Triggering edge depends on CLKXP.
	//				3	In SPI mode, clock starts without delay. Triggering edge depends on CLKXP.
	//	10-8	RESERVED
	//	7	DXENA	DX Enable. If set, DX is enabled.
	//	6	RESERVED
	//	5-4	RINTM	Receive Interupt (RINT) Enable.
	//				0	RINT driven by RRDY, end of word and end of frame
	//				1	RINT generated by end of block and end of frame
	//				2	RINT generated by new frame sync
	//				3	RINT generated by RSYNCERR
	//	3	RSYNCERR Receive Sync Error. If set then error has been detected.
	//	2	RFULL	Receive Shift Register Full. If set then RSR is full.				STATUS
	//	1	RRDY	Receiver Ready. If set then receiver ready for new data in DRR to be read.	STATUS
	//	0	RRST	Receiver Reset. If not set then receiver disabled.
	MCBSP_FMKS(SPCR, FREE, NO) |		//Do not run clock when halted
	MCBSP_FMKS(SPCR, SOFT, NO) |		//Clocks stop instantly
	MCBSP_FMKS(SPCR, FRST, YES) |		//Generate Frame Sync
	MCBSP_FMKS(SPCR, GRST, YES) |		//Generate Sample Rate
	MCBSP_FMKS(SPCR, XINTM, XRDY) |		//XINT driven by XRDY
	MCBSP_FMKS(SPCR, XSYNCERR, NO) |	//Error checking used
	MCBSP_FMKS(SPCR, XRST, YES) |		//Enable Transmitter
	MCBSP_FMKS(SPCR, DLB, OFF) |		//No digital loop back
	MCBSP_FMKS(SPCR, RJUST, RZF) |		//Right justify, 0 fill
	MCBSP_FMKS(SPCR, CLKSTP, DISABLE) |	//Clock stop disabled
	MCBSP_FMKS(SPCR, DXENA, OFF) |		//DX disabled
	MCBSP_FMKS(SPCR, RINTM, RRDY) |		//RINT driven by RRDY
	MCBSP_FMKS(SPCR, RSYNCERR, NO) |	//Error checking used
	MCBSP_FMKS(SPCR, RRST, YES),		//Enable Receiver
	
	//RCR - Receive Control Register
	//	31	RPHASE	Receive phases
	//				0	Single Phase
	//				1	Dual Phase
	//	30-24	RFRLEN2	Phase 2 receive word length
	//				0	1 word
	//				1	2 words
	//				2	3 words
	//				...	...
	//				0x7F	128 words
	//	23-21	RWDLEN2	Phase 2 receive word length
	//				0	8 bits
	//				1	12 bits
	//				2	16 bits
	//				3	20 bits
	//				4	24 bits
	//				5	32 bits
	//				6-7	RESERVED
	//	20-19	RCOMPAND Receive Companding, modes other than 0 only apply when RWDLEN1/2 are 0
	//				0	No companding, 8bit MSB first
	//				1	No companding, 8bit LSB first
	//				2	Compand using µ-law
	//				3	Compand using A-law
	//	18	RFIG	Receive frame ignore
	//				0	Receive frame sync restarts transfer
	//				1	Receive frame sync pulses after first pulse ignored
	//	17-16	RDATDLY	Receive Data Delay
	//				0	0 bit delay
	//				1	1 bit delay
	//				2	2 bit delay
	//				3	RESERVED
	//	15	RESERVED
	//	14-8	RFRLEN1	Phase 1 receive word length
	//				0	1 word
	//				1	2 words
	//				2	3 words
	//				...	...
	//				0x7F	128 words
	//	7-5	RWDLEN1	Phase 1 receive word length
	//				0	8 bits
	//				1	12 bits
	//				2	16 bits
	//				3	20 bits
	//				4	24 bits
	//				5	32 bits
	//				6-7	RESERVED
	//	4	RWDREVRS Receive 32 bit reversal enable. If set 32-bit reversal enabled. RWDLEN1/2 should be 0x5 and RCOMPAND should be 0x1
	//	3-0	RESERVED
	MCBSP_FMKS(RCR, RPHASE, SINGLE) |	//Single Phase
	MCBSP_FMKS(RCR, RFRLEN2, DEFAULT) |	//1 word
	MCBSP_FMKS(RCR, RWDLEN2, DEFAULT) |	//8 bits
	MCBSP_FMKS(RCR, RCOMPAND, MSB) |	//No companding, 8 bit MSB first
	MCBSP_FMKS(RCR, RFIG, NO) |			//Receive frame does not restart transfer
	MCBSP_FMKS(RCR, RDATDLY, 0BIT) |	//0 bit delay
	MCBSP_FMKS(RCR, RFRLEN1, OF(0)) |	//1 word
	MCBSP_FMKS(RCR, RWDLEN1, 32BIT) |	//32 bits
	MCBSP_FMKS(RCR, RWDREVRS, DISABLE),	//32 bit reversal disabled
	
	//XCR - Transmit Control Register
	//	31	XPHASE	Transmit phases
	//				0	Single Phase
	//				1	Dual Phase
	//	30-24	XFRLEN2	Phase 2 transmit word length
	//				0	1 word
	//				1	2 words
	//				2	3 words
	//				...	...
	//				0x7F	128 words
	//	23-21	XWDLEN2	Phase 2 transmit word length
	//				0	8 bits
	//				1	12 bits
	//				2	16 bits
	//				3	20 bits
	//				4	24 bits
	//				5	32 bits
	//				6-7	RESERVED
	//	20-19	XCOMPAND Transmit Companding, modes other than 0 only apply when RWDLEN1/2 are 0
	//				0	No companding, 8bit MSB first
	//				1	No companding, 8bit LSB first
	//				2	Compand using µ-law
	//				3	Compand using A-law
	//	18	XFIG	Transmit frame ignore
	//				0	Transmit frame sync restarts transfer
	//				1	Transmit frame sync pulses after first pulse ignored
	//	17-16	XDATDLY	Transmit Data Delay
	//				0	0 bit delay
	//				1	1 bit delay
	//				2	2 bit delay
	//				3	RESERVED
	//	15	RESERVED
	//	14-8	XFRLEN1	Phase 1 transmit word length
	//				0	1 word
	//				1	2 words
	//				2	3 words
	//				...	...
	//				0x7F	128 words
	//	7-5	XWDLEN1	Phase 1 transmit word length
	//				0	8 bits
	//				1	12 bits
	//				2	16 bits
	//				3	20 bits
	//				4	24 bits
	//				5	32 bits
	//				6-7	RESERVED
	//	4	XWDREVRS Transmit 32 bit reversal enable. If set 32-bit reversal enabled. XWDLEN1/2 should be 0x5 and XCOMPAND should be 0x1
	//	3-0	RESERVED
	MCBSP_FMKS(XCR, XPHASE, SINGLE) |	//Single Phase
	MCBSP_FMKS(XCR, XFRLEN2, DEFAULT) |	//1 word
	MCBSP_FMKS(XCR, XWDLEN2, DEFAULT) |	//8 bits
	MCBSP_FMKS(XCR, XCOMPAND, MSB) |	//No companding, 8 bit MSB first
	MCBSP_FMKS(XCR, XFIG, NO) |			//Transmit frame does not restart transfer
	MCBSP_FMKS(XCR, XDATDLY, 0BIT) |	//0 bit delay
	MCBSP_FMKS(XCR, XFRLEN1, OF(0)) |	//1 word
	MCBSP_FMKS(XCR, XWDLEN1, 32BIT) |	//32 bits
	MCBSP_FMKS(XCR, XWDREVRS, DEFAULT),	//32 bit reversal disabled
	
	//SRGR - Sample Rate Generator Register
	//	31	GSYNC	Sample rate generator clock (CLKG) sync. If not set CLKG free running, else is resynced
	//	30	CLKSP	CLGS polarity. If not set, rising edge of CLKS generates CLKG and FSG, else falling edge generates them.
	//	29	CLKSM	McBSP sample rate generator clock mode. If not set sample generator clock derived from CLKS, else from CPU clock.
	//	28	FSGM	Sample rate transmit frame sync. Only used when FSMX in PCR is 1
	//				0	Transmit frame sync (FSX) generated on every DXR-XSR copy. FWID and FPER ignored.
	//				1	Transmit frame sync generated by FSG
	//	27-16	FPER	FPER + 1 specifies how many CLKG periods between frame sync signals
	//	15-8	FWID	FWID + 1 specifies how long the frame sync pulse is active
	//	7-0	CLKGDV	Divider between CLKG and sample rate generator clock
	MCBSP_FMKS(SRGR, GSYNC, DEFAULT) |	//Free running
	MCBSP_FMKS(SRGR, CLKSP, DEFAULT) |	//Rising edge
	MCBSP_FMKS(SRGR, CLKSM, DEFAULT) |	//CPU clock
	MCBSP_FMKS(SRGR, FSGM, DEFAULT) |	//On DXR-XSR copy
	MCBSP_FMKS(SRGR, FPER, DEFAULT) |	//1 CLKG period between frame syncs
	MCBSP_FMKS(SRGR, FWID, DEFAULT) |	//20 lengths active
	MCBSP_FMKS(SRGR, CLKGDV, DEFAULT),	//Divide by 100
	
	//MCR - Multi-channel Control Register
	//	31-26	RESERVED
	//	25	XMCME	128 channel selection.
	//				0	32 channel mode
	//				1	128 channel mode, XCER1-3 used
	//	24-23	XPBBLK	Transmit partition B subframe
	//				0	Subframe 1. Channels 16-31
	//				1	Subframe 3. Channels 48-63
	//				2	Subframe 5. Channels 80-95
	//				3	Subframe 7. Channels 112-127
	//	22-21	XPABLK	Transmit partition A subframe
	//				0	Subframe 0. Channels 0-15
	//				1	Subframe 2. Channels 32-47
	//				2	Subframe 4. Channels 64-79
	//				3	Subframe 6. Channels 96-111
	//	20-18	XCBLK	Transmit current subframe
	//				0	Subframe 0. Channels 0-15
	//				1	Subframe 1. Channels 16-31
	//				2	Subframe 2. Channels 32-47
	//				3	Subframe 3. Channels 48-63
	//				4	Subframe 4. Channels 64-79
	//				5	Subframe 5. Channels 80-95
	//				6	Subframe 6. Channels 96-111
	//				7	Subframe 7. Channels 112-127
	//	17-16	XMCM	Transmit Multi-Channel selection enable
	//				0	All channels transmitted without masking
	//				1	All channels disabled and masked by default. Select and unmask using XP[A/B]BLK and XCER[A/B]
	//				2	All channels enabled but masked. Select and unmask using XP[A/B]BLK and XCER[A/B]
	//				3	All channels disabled and masked by default. Select using RP[A/B]BLK and RCER[A/B]. Unmask using RP[A/B]BLK and XCER[A/B]
	//	15-10	RESERVED
	//	9	RMCME	128 channel selection.
	//				0	32 channel mode
	//				1	128 channel mode, XCER1-3 used
	//	8-7	RPBBLK	Receive partition B subframe
	//				0	Subframe 1. Channels 16-31
	//				1	Subframe 3. Channels 48-63
	//				2	Subframe 5. Channels 80-95
	//				3	Subframe 7. Channels 112-127
	//	6-5	RPABLK	Receive partition A subframe
	//				0	Subframe 0. Channels 0-15
	//				1	Subframe 2. Channels 32-47
	//				2	Subframe 4. Channels 64-79
	//				3	Subframe 6. Channels 96-111
	//	4-2	RCBLK	Receive current subframe
	//				0	Subframe 0. Channels 0-15
	//				1	Subframe 1. Channels 16-31
	//				2	Subframe 2. Channels 32-47
	//				3	Subframe 3. Channels 48-63
	//				4	Subframe 4. Channels 64-79
	//				5	Subframe 5. Channels 80-95
	//				6	Subframe 6. Channels 96-111
	//				7	Subframe 7. Channels 112-127
	//	1	RESERVED
	//	0	RMCM	Receive Multi-Channel selection enable
	//				0	All channels received without masking
	//				1	All channels disabled and masked by default. Select and unmask using RP[A/B]BLK and RCER[A/B]
	MCBSP_MCR_DEFAULT,
	
	//RCER - Receive Channel Enable Register
	//	31-16	RCEB	Receive Channel Enable partition B
	//				Bitwise, if set then nth channel enabled in the selected subframe
	//	15-0	RCEA	Receive Channel Enable partition A
	//				Bitwise, if set then nth channel enabled in the selected subframe
	MCBSP_RCER_DEFAULT,	//All disabled
	
	//XCER - Transmit Channel Enable Register
	//	31-16	XCEB	Transmit Channel Enable partition
	//				Bitwise, if set then nth channel enabled in the selected subframe
	//	15-0	XCEA	Transmit Channel Enable partition
	//				Bitwise, if set then nth channel enabled in the selected subframe
	MCBSP_XCER_DEFAULT,	//All disabled
	
	//PCR - Pin Control Register
	//	31-14	RESERVED
	//	13	XIOEN	Transmit GPIO mode
	//				0	DX, FSX and CLKX set as serial pins, not GPIO pins
	//				1	DX configured as GP output, FSX and CLKX set as GPIO
	//	12	RIOEN	Receive GPIO mode
	//				0	DR, FSR, CLKR, and CLKS pins set as serial pins, not GPIO
	//				1	DR and CLKS configured as GP input, FSR and CLKR set as GPIO
	//	11	FSXM	Transmit Frame Sync Mode
	//				0	Frame sync derived from external source
	//				1	Frame sync determined by FSGM in SRGR
	//	10	FSRM	Receive Frame Sync Mode
	//				0	Frame sync derived from external source. FSR is an input pin
	//				1	Frame sync determined generated by sample rate generator
	//	9	CLKXM	Transmitter Clock Mode
	//				0	CLKX is an input pin, driven by external clock
	//					SPI Mode: McBSP is a slave and driven by SPI master, CLKR driven by CLKX
	//				1	CLKX is an output pin, driven by sample rate generator
	//					SPI Mode: McBSP is master and generates CLKX and CLKR, drives the clock of the SPI slaves
	//	8	CLKRM	Receive Clock Mode
	//				Digital Loop Back Disabled:
	//				0	CLKR is an input pin and driven by external clock
	//				1	CLKR is an output pin and driven by sample rate generator
	//				Digital Loop Back Enabled:
	//				0	Receive clock driven by CLKX based on CLKXM. CLKR pin high impedance
	//				1	CLKR is an output pin driven by transmit clock based on CLKXM
	//	7	RESERVED
	//	6	CLKSSTAT CLKS pin status				STATUS
	//				0	CLKS low
	//				1	CLKS high
	//	5	DXSTAT	DX pin status					STATUS
	//				0	DX low
	//				1	DX high
	//	4	DRSTAT	DR pin status					STATUS
	//				0	DR low
	//				1	DR high
	//	3	FSXP	Transmit Frame Sync Polarity
	//				0	Transmit frame sync active high
	//				1	Transmit frame sync active low
	//	2	FSRP	Receive Frame Sync Polarity
	//				0	Receive frame sync active high
	//				1	Receive frame sync active low
	//	1	CLKXP	Transmit Clock Polarity
	//				0	Transmit data sampled on rising edge of CLKX
	//				1	Transmit data sampled on falling edge of CLKX
	//	0	CLKRP	Receive Clock Polarity
	//				0	Receive data sampled on rising edge of CLKR
	//				1	Receive data sampled on falling edge of CLKR
	MCBSP_FMKS(PCR, XIOEN, SP) |		//DX, FSX and CLKX serial pins
	MCBSP_FMKS(PCR, RIOEN, SP) |		//DR, FSR, CLKR and CLKS serial pins
	MCBSP_FMKS(PCR, FSXM, EXTERNAL) |	//Use external clock
	MCBSP_FMKS(PCR, FSRM, EXTERNAL) |	//Use external clock
	MCBSP_FMKS(PCR, CLKXM, INPUT) |		//CLKX input pin
	MCBSP_FMKS(PCR, CLKRM, INPUT) |		//CLKR input pin
	MCBSP_FMKS(PCR, CLKSSTAT, DEFAULT) |//
    MCBSP_FMKS(PCR, DXSTAT, DEFAULT) |	//DX pin low
	MCBSP_FMKS(PCR, FSXP, ACTIVEHIGH) |	//Active high
	MCBSP_FMKS(PCR, FSRP, ACTIVEHIGH) |	//Active high
	MCBSP_FMKS(PCR, CLKXP, FALLING) |	//Sampled on falling edge
	MCBSP_FMKS(PCR, CLKRP, RISING)		//Sampled on rising edge
};

MCBSP_Config mcbsp_control_config = {
	//SPCR - Serial Port Control Register
	MCBSP_FMKS(SPCR, FREE, NO) |		//Do not run clock when halted
	MCBSP_FMKS(SPCR, SOFT, NO) |		//Clocks stop instantly
	MCBSP_FMKS(SPCR, FRST, YES) |		//Generate Frame Sync
	MCBSP_FMKS(SPCR, GRST, YES) |		//Generate Sample Rate
	MCBSP_FMKS(SPCR, XINTM, XRDY) |		//XINT driven by XRDY
	MCBSP_FMKS(SPCR, XSYNCERR, NO) |	//Error checking used
	MCBSP_FMKS(SPCR, XRST, YES) |		//Enable Transmitter
	MCBSP_FMKS(SPCR, DLB, OFF) |		//No digital loop back
	MCBSP_FMKS(SPCR, RJUST, RZF) |		//Right justify, 0 fill
	MCBSP_FMKS(SPCR, CLKSTP, NODELAY) |	//No clock delay in SPI mode
	MCBSP_FMKS(SPCR, DXENA, OFF) |		//DX disabled
	MCBSP_FMKS(SPCR, RINTM, RRDY) |		//RINT driven by RRDY
	MCBSP_FMKS(SPCR, RSYNCERR, NO) |	//Error checking used
	MCBSP_FMKS(SPCR, RRST, YES),		//Enable Receiver
	
	//RCR - Receive Control Register
	MCBSP_FMKS(RCR, RPHASE, DEFAULT) |	//Single Phase
	MCBSP_FMKS(RCR, RFRLEN2, DEFAULT) |	//1 word
	MCBSP_FMKS(RCR, RWDLEN2, DEFAULT) |	//8 bits
	MCBSP_FMKS(RCR, RCOMPAND, DEFAULT) |	//No companding, 8 bit MSB first
	MCBSP_FMKS(RCR, RFIG, DEFAULT) |	//Receive frame restarts transfer
	MCBSP_FMKS(RCR, RDATDLY, DEFAULT) |	//0 bit delay
	MCBSP_FMKS(RCR, RFRLEN1, DEFAULT) |	//1 word
	MCBSP_FMKS(RCR, RWDLEN1, DEFAULT) |	//8 bits
	MCBSP_FMKS(RCR, RWDREVRS, DEFAULT),	//32 bit reversal disabled
	
	//XCR - Transmit Control Register
	MCBSP_FMKS(XCR, XPHASE, SINGLE) |	//Single Phase
	MCBSP_FMKS(XCR, XFRLEN2, OF(0)) |	//1 word
	MCBSP_FMKS(XCR, XWDLEN2, 8BIT) |	//8 bits
	MCBSP_FMKS(XCR, XCOMPAND, MSB) |	//No companding, 8 bit MSB first
	MCBSP_FMKS(XCR, XFIG, NO) |			//Transmit frame restarts transfer
	MCBSP_FMKS(XCR, XDATDLY, 1BIT) |	//0 bit delay
	MCBSP_FMKS(XCR, XFRLEN1, OF(0)) |	//1 word
	MCBSP_FMKS(XCR, XWDLEN1, 16BIT) |	//8 bits
	MCBSP_FMKS(XCR, XWDREVRS, DISABLE),	//32 bit reversal disabled
	
	//SRGR - Sample Rate Generator Register
	MCBSP_FMKS(SRGR, GSYNC, FREE) |		//Free running
	MCBSP_FMKS(SRGR, CLKSP, RISING) |	//Rising edge
	MCBSP_FMKS(SRGR, CLKSM, INTERNAL) |	//CPU clock
	MCBSP_FMKS(SRGR, FSGM, DXR2XSR) |	//On DXR-XSR copy
	MCBSP_FMKS(SRGR, FPER, OF(0)) |		//1 CLKG period between frame syncs
	MCBSP_FMKS(SRGR, FWID, OF(19)) |	//20 lengths active
	MCBSP_FMKS(SRGR, CLKGDV, OF(99)),	//Divide by 100
	
	//MCR - Multi-channel Control Register
	MCBSP_MCR_DEFAULT,
	
	//RCER - Receive Channel Enable Register
	MCBSP_RCER_DEFAULT,	//All disabled
	
	//XCER - Transmit Channel Enable Register
	MCBSP_XCER_DEFAULT,	//All disabled
	
	//PCR - Pin Control Register
	MCBSP_FMKS(PCR, XIOEN, SP) |		//DX, FSX and CLKX serial pins
	MCBSP_FMKS(PCR, RIOEN, SP) |		//DR, FSR, CLKR and CLKS serial pins
	MCBSP_FMKS(PCR, FSXM, INTERNAL) |	//Use internal clock
	MCBSP_FMKS(PCR, FSRM, EXTERNAL) |	//Use external clock
	MCBSP_FMKS(PCR, CLKXM, OUTPUT) |	//McBSP is master and drives CLKX pin
	MCBSP_FMKS(PCR, CLKRM, INPUT) |		//CLKR input pin
	MCBSP_FMKS(PCR, CLKSSTAT, DEFAULT) |//
	MCBSP_FMKS(PCR, DXSTAT, DEFAULT) |	//DX pin low
	MCBSP_FMKS(PCR, FSXP, ACTIVELOW) |	//Active low
	MCBSP_FMKS(PCR, FSRP, DEFAULT) |	//Active high
	MCBSP_FMKS(PCR, CLKXP, FALLING) |	//Sampled on falling edge
	MCBSP_FMKS(PCR, CLKRP, DEFAULT)		//Sampled on falling edge
};
//extern volatile int32_t *buf_l, *buf_r;

/*#pragma vector=YKNOW_THAT_VECTOR
__interrupt void newSample()
{
	
}

#pragma vector=YKNOW_THAT_OTHER_VECTOR
__interrupt void sendSample()
{
	
}*/

void mcbspSetup()
{
	mcbspControlHandle = MCBSP_open(MCBSP_DEV0, MCBSP_OPEN_RESET);
	mcbspDataHandle = MCBSP_open(MCBSP_DEV1, MCBSP_OPEN_RESET);
	if(mcbspControlHandle == INV || mcbspDataHandle == INV)
	{
		return;
	}
	MCBSP_config(mcbspControlHandle, &mcbsp_control_config);
	MCBSP_config(mcbspDataHandle, &mcbsp_data_config);
	MCBSP_start(mcbspControlHandle, MCBSP_XMIT_START | MCBSP_RCV_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC, 220);
	DSK6713_AIC23_rset(0, DSK6713_AIC23_RESET, 0);

	DSK6713_AIC23_config(AIC23_CODEC_ID, &aic23_config);
	if (MCBSP_rrdy(mcbspDataHandle))
		MCBSP_read(mcbspDataHandle);
	MCBSP_start(mcbspDataHandle, MCBSP_XMIT_START | MCBSP_RCV_START | MCBSP_SRGR_START | MCBSP_SRGR_FRAMESYNC, 220);
}

void codecSetup()
{
	mcbspSetup();
}

void getData(int32_t * ptr)
{
	while(1)
	{
		if (MCBSP_rrdy(mcbspDataHandle))
		{
			*ptr = MCBSP_read(mcbspDataHandle);
			break;
		}
	}
}

void sendData(int32_t * ptr)
{
	while(1)
	{
		if(MCBSP_rrdy(mcbspDataHandle))
		{
			MCBSP_write(mcbspDataHandle, *ptr);
			break;
		}
	}
}
