## Makefile for STM32F4
# @author Thomas Reidemeister <treideme@uwaterloo.ca>
# @date 2013.01.27
TARGET=main
EXECUTABLE=main.elf

## Tool configuration
CC=/opt/codesourcery/bin/arm-none-eabi-gcc
LD=/opt/codesourcery/bin/arm-none-eabi-gcc
AR=/opt/codesourcery/bin/arm-none-eabi-ar
AS=/opt/codesourcery/bin/arm-none-eabi-as
CP=/opt/codesourcery/bin/arm-none-eabi-objcopy
OD=/opt/codesourcery/bin/arm-none-eabi-objdump
BIN=$(CP) -O ihex

## Flags
LDFLAGS=-Wl,-T,stm32_flash.ld
CPU=cortex-m4
DEFS=-DUSE_STDPERIPH_DRIVER
OPTIMIZE=-O0 -g
MCFLAGS= -fno-common -mcpu=$(CPU) -mthumb -mthumb-interwork -Wall -std=c99 -mfloat-abi=softfp -mfpu=fpv4-sp-d16
#MISRA=-C99

## Configuration of paths
ROOT=Libraries
## Individual libraries
CORE=$(ROOT)/CMSIS/Include
DEVICE=$(ROOT)/Device/STM32F4xx
PERIPH=$(ROOT)/STM32F4xx_StdPeriph_Driver

STM32_INCLUDES = -I./src \
	-I$(CORE) \
	-I$(DEVICE)/Include \
	-I$(PERIPH)/inc/

CFLAGS	= $(MCFLAGS) $(OPTIMIZE) $(DEFS) $(STM32_INCLUDES)
#$(MISRA)
AFLAGS	= $(MCFLAGS)

SRC = src/main.c \
	  src/STM_Peripherals.c \
	  src/UART_Debug.c \
	  src/newlib_stubs.c \
	  src/system_stm32f4xx.c \
	  $(PERIPH)/src/stm32f4xx_rcc.c \
	  $(PERIPH)/src/stm32f4xx_exti.c \
	  $(PERIPH)/src/stm32f4xx_syscfg.c \
	  $(PERIPH)/src/stm32f4xx_gpio.c \
	  $(PERIPH)/src/stm32f4xx_tim.c \
	  $(PERIPH)/src/misc.c

STARTUP = startup_stm32f4xx.s

OBJDIR = .
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

all: $(TARGET).hex
	@echo "*** Build Complete ***"

$(TARGET).hex: $(EXECUTABLE)
	$(CP) -O ihex $^ $@

$(EXECUTABLE): $(SRC) $(STARTUP)
	$(CC) $(CFLAGS) $(LDFLAGS) $^  -o $@ -lm 
	$(OD) -h -S $@ > $(TARGET).lst

program: $(TARGET).hex
	/opt/codesourcery/bin/openocd -f openocd.cfg
	@echo "*** STM32F4 Programming Complete ***"

clean:
	rm -f $(TARGET)  $(TARGET).lst $(OBJ) $(AUTOGEN)  $(TARGET).out  $(TARGET).hex  $(TARGET).map \
	 $(TARGET).dmp  $(TARGET).elf
	@echo "*** Project Cleaned ***"
