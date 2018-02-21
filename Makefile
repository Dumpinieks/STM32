file ?= main
OUTPUT_NAME ?= $(file)
LINKER = lib/STM32F103XB_FLASH.ld
OBJECTS ?= objects/startup_stm32f103xb.o
OBJECTS += objects/main.o
OBJECTS += objects/system_stm32f1xx.o
CFLAGS = -Wall
OBJECT = arm-none-eabi-gcc $(CFLAGS) --std=c99 -g3 -mthumb
OBJECT += -mcpu=cortex-m3 -ffreestanding -DDEBUG -DSTM32F103xB -Ilib/ -c
COMP = arm-none-eabi-gcc $(CFLAGS) -Wl,-T$(LINKER) --std=c99 
COMP += --specs=nosys.specs -mthumb -mcpu=cortex-m3 $(OBJECTS) -o
BINARY = arm-none-eabi-objcopy -O binary elf/$(file).elf

vpath %.o objects/
vpath %.c source/
vpath %.s source/
vpath %.h lib/
vpath %.ld lib/
vpath %.elf elf/

assembling: folders deleteF $(file).bin
	@echo "Success"

$(file).bin: object elf
	@$(BINARY) $(OUTPUT_NAME).bin
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
	@socat -,raw,echo=0,escape=0x03 /dev/ttyUSB0,b600,raw,echo=0
