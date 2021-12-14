################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/AES.c \
../source/AESTesting.c \
../source/PESFinalProject.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/spi.c 

OBJS += \
./source/AES.o \
./source/AESTesting.o \
./source/PESFinalProject.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/spi.o 

C_DEPS += \
./source/AES.d \
./source/AESTesting.d \
./source/PESFinalProject.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/spi.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\Fall2021\PES\FinalProject\IntegrationOfLibrary\PESFinalProject\board" -I"D:\Fall2021\PES\FinalProject\IntegrationOfLibrary\PESFinalProject\include" -I"D:\Fall2021\PES\FinalProject\IntegrationOfLibrary\PESFinalProject\library" -I"D:\Fall2021\PES\FinalProject\IntegrationOfLibrary\PESFinalProject\source" -I"D:\Fall2021\PES\FinalProject\IntegrationOfLibrary\PESFinalProject" -I"D:\Fall2021\PES\FinalProject\IntegrationOfLibrary\PESFinalProject\drivers" -I"D:\Fall2021\PES\FinalProject\IntegrationOfLibrary\PESFinalProject\CMSIS" -I"D:\Fall2021\PES\FinalProject\IntegrationOfLibrary\PESFinalProject\utilities" -I"D:\Fall2021\PES\FinalProject\IntegrationOfLibrary\PESFinalProject\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


