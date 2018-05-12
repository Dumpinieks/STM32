file ?= main
LINKER = lib/STM32F103XB_FLASH.ld
OBJECTS ?= objects/startup_stm32f103xb.o
OBJECTS += objects/$(file).o
OBJECTS += objects/system_stm32f1xx.o
CFLAGS = -Wall
OBJECT = $(COMPILER_DIR)/arm-none-eabi-gcc $(CFLAGS) --std=c99 -g3 -mthumb
OBJECT += -mcpu=cortex-m3 -ffreestanding -DDEBUG -DSTM32F103xB -Ilib/ -c
COMP = $(COMPILER_DIR)/arm-none-eabi-gcc $(CFLAGS) -Wl,-T$(LINKER) --std=c99 
COMP += --specs=nosys.specs -mthumb -mcpu=cortex-m3 $(OBJECTS) -o
BINARY = $(COMPILER_DIR)/arm-none-eabi-objcopy -O binary elf/$(file).elf
COMPILER_DIR := $(HOME)/opt/gcc-arm-none-eabi-7-2017-q4-major/bin

vpath %.o objects/
vpath %.c source/
vpath %.s source/
vpath %.h lib/
vpath %.ld lib/
vpath %.elf elf/

load: assembling flash

assembling: folders deleteF $(file).bin
	@echo "Success"

usart: load socat

$(file).bin: object elf
	@$(BINARY) $(file).bin
	@echo "Created "$@

deleteF:
	@rm -f *.bin objects/*.o elf/*.elf

folders:
	@mkdir -p objects
	@mkdir -p elf

object: $(file).o startup_stm32f103xb.o system_stm32f1xx.o

elf: $(file).elf

%.o: %.c
	@$(OBJECT) $^
	@mv $@ objects/
	@echo "Created "$@

%.o: %.s
	@$(OBJECT) $^
	@mv $@ objects/
	@echo "Created "$@

%.elf:
	@$(COMP) $(file).elf
	@mv $@ elf/
	@echo "Created "$@

flash:
	@st-flash write $(file).bin 0x8000000

socat:
	@sudo socat -,raw,echo=0,escape=0x03 /dev/ttyUSB0,b9600,raw,echo=0
