SOURCE ?= main.c
OUTPUT_NAME ?= main
CFLAGS ?= -Wall
LINKER ?= STM32F103XB_FLASH.ld
OBJECT = --std=c99 -g3 -mthumb -mcpu=cortex-m3 -ffreestanding -DDEBUG -DSTM32F103xB -c

release: object compile binary
	@echo "Success"

object:	$(OUTPUT_NAME).o startup_stm32f103xb.o system_stm32f1xx.o

compile: $(OUTPUT_NAME).o startup_stm32f103xb.o system_stm32f1xx.o
	@arm-none-eabi-gcc $(CFLAGS) -Wl,-T$(LINKER) --std=c99 --specs=nosys.specs -mthumb -mcpu=cortex-m3 startup_stm32f103xb.o $(OUTPUT_NAME).o system_stm32f1xx.o -o $(OUTPUT_NAME).elf
	@echo "Created "$(OUTPUT_NAME).elf

binary:
	@arm-none-eabi-objcopy -O binary $(OUTPUT_NAME).elf $(OUTPUT_NAME).bin
	@echo "Created "$(OUTPUT_NAME).bin

delete:
	@rm -f *.o *.elf *.bin

flash:
	@st-flash write $(OUTPUT_NAME).bin 0x8000000

$(OUTPUT_NAME).o:
	@arm-none-eabi-gcc $(CFLAGS) $(OBJECT) $(SOURCE)
	@echo "Created "$(OUTPUT_NAME).o

startup_stm32f103xb.o:
	@arm-none-eabi-gcc $(CFLAGS) $(OBJECT) startup_stm32f103xb.s
	@echo "Created startup_stm32f103xb.o"

system_stm32f1xx.o:
	@arm-none-eabi-gcc $(CFLAGS) $(OBJECT) system_stm32f1xx.c
	@echo "Created system_stm32f1xx.o"

