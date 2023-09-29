ROOTDIR=src
NAME=robo

CC=arm-none-eabi-gcc
CPU=cortex-m0plus
OPTIMIZATION=-O0
IPATH=-I CMSIS
LPATH=-L Linker
# -g : gives debugging information for using F5 Cortex-Debug
# --specs=nano.specs : New nano-Standard C lib
# -mfloat-abi=soft : Software Library for calculating float point arithmetic
# -mfloat-abi=hard : Hardware Library for calculating floating point arithmetic if it supports that, but should be enabled on Hardware first!

CFLAGS=-c -mcpu=$(CPU) -g -mthumb -mfloat-abi=soft -std=c99 -Wall $(OPTIMIZATION)
LDFLAGS=-mcpu=$(CPU) -mthumb -mfloat-abi=soft --specs=nano.specs $(LPATH) -T stm32_ls.ld -Wl,-Map=$(NAME).map
HEX=arm-none-eabi-objcopy

all:main.o syscalls.o startup.o system_stm32l0xx.o gpio.o rcc.o adc.o pwm.o uart.o i2c.o led.o dc_motor.o exti.o syscfg.o servo.o systick.o $(NAME).elf size

main.o:$(ROOTDIR)/main.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

startup.o:Startup/startup.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

system_stm32l0xx.o:CMSIS/system_stm32l0xx.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

syscalls.o:CMSIS/syscalls.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

gpio.o:$(ROOTDIR)/gpio.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

adc.o:$(ROOTDIR)/adc.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

exti.o:$(ROOTDIR)/exti.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

pwm.o:$(ROOTDIR)/pwm.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

dc_motor.o:$(ROOTDIR)/dc_motor.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

syscfg.o:$(ROOTDIR)/syscfg.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

timer.o:$(ROOTDIR)/timer.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

uart.o:$(ROOTDIR)/uart.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

i2c.o:$(ROOTDIR)/i2c.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

rcc.o:$(ROOTDIR)/rcc.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

led.o:$(ROOTDIR)/led.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

lcd.o:$(ROOTDIR)/lcd.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

servo.o:$(ROOTDIR)/servo.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

systick.o:$(ROOTDIR)/systick.c
	$(CC) $(CFLAGS) $(IPATH) $^ -o build/$@

$(NAME).elf:
	$(CC) $(LDFLAGS) build/*.o -lgcc -o build/$@

hex:
	$(HEX) -O ihex build/$(NAME).elf build/$(NAME).hex

bin:
	$(HEX) -O binary build/$(NAME).elf build/$(NAME).bin

clean:
	rm -rf build/*.*
	rm -rf $(NAME).map
	rm -rf firmware.bin

check:
	cppcheck --enable=all --addon=cert $(ROOTDIR)/*.c

load:
	openocd -f interface/stlink-v2-1.cfg -f target/stm32l0.cfg -c "program build/$(NAME).elf verify reset exit"

debug:
	arm-none-eabi-gdb

size:
	arm-none-eabi-size build/$(NAME).elf

read:
	openocd -f interface/stlink-v2-1.cfg -f target/stm32l0.cfg -c "init" -c "reset init" -c "flash read_bank 0 firmware.bin 0 0x8000" -c "exit"

.phony: test all hex bin clean load debug size check run read
