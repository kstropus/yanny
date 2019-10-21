# Don't use normal gcc, use the arm cross compiler
#CC = ~/gcc-arm-none-eabi-8-2019-q3-update/bin/arm-none-eabi-gcc
CC = aarch64-elf-gcc
LD = aarch64-elf-ld

CFLAGS= -nostdinc -nostdlib -nostartfiles
CSRCFLAGS= -Wall -O2 -ffreestanding -fno-stack-protector
LFLAGS= -nostdinc -nostdlib -nostartfiles

# Location of the files
KER_SRC = ../src/kernel
KER_HEAD = ../include
COMMON_SRC = ../src/common
OBJ_DIR = objects
KERSOURCES = $(wildcard $(KER_SRC)/*.c)
COMMONSOURCES = $(wildcard $(COMMON_SRC)/*.c)
ASMSOURCES = $(wildcard $(KER_SRC)/*.S)
OBJECTS = $(patsubst $(KER_SRC)/%.c, $(OBJ_DIR)/%.o, $(KERSOURCES))
OBJECTS += $(patsubst $(COMMON_SRC)/%.c, $(OBJ_DIR)/%.o, $(COMMONSOURCES))
OBJECTS += $(patsubst $(KER_SRC)/%.S, $(OBJ_DIR)/%.o, $(ASMSOURCES))
HEADERS = $(wildcard $(KER_HEAD)/*.h)

IMG_NAME=kernel8.img

build: $(OBJECTS) $(HEADERS)
	echo $(OBJECTS)
	$(LD) $(LFLAGS) $(OBJECTS) -T link.ld -o kernel.elf
	aarch64-elf-objcopy -O binary kernel.elf $(IMG_NAME)

$(OBJ_DIR)/%.o: $(KER_SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS)

$(OBJ_DIR)/%.o: $(KER_SRC)/%.S
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -c $< -o $@

$(OBJ_DIR)/%.o: $(COMMON_SRC)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(KER_SRC) -I$(KER_HEAD) -c $< -o $@ $(CSRCFLAGS)

clean:
	rm -rf $(OBJ_DIR)
	rm kernel.elf
	rm $(IMG_NAME)

run: build
	qemu-system-aarch64 -M raspi3 -nographic -monitor none -serial stdio -kernel $(IMG_NAME)
