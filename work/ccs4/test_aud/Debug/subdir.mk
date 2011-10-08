################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ring.c 

OBJS += \
./ring.obj 

C_DEPS += \
./ring.pp 

OBJS__QTD += \
".\ring.obj" 

C_DEPS__QTD += \
".\ring.pp" 

C_SRCS_QUOTED += \
"../ring.c" 


# Each subdirectory must supply rules for building sources it contributes
ring.obj: ../ring.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c6000/bin/cl6x" -mv6700 -g --define="CHIP_6713" --define="_DEBUG" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c6000/include" --include_path="C:/Program Files (x86)/Texas Instruments/xdais_7_10_00_06/packages/ti/xdais" --include_path="C:/Users/Thomas/Documents/workspace/test_aud/Debug" --include_path="/include" --diag_warning=225 --preproc_with_compile --preproc_dependency="ring.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


