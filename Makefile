
PREFIX = $(shell pwd)
DEST_DIR = $(PREFIX)/bin
BUILD_DIR = $(PREFIX)/build
SRC_DIR = $(PREFIX)/kernel
CC_VERSION = gcc-7.5.0
CROSS_CC_DIR = $(BUILD_DIR)/$(CC_VERSION)/bin

QEMU = /mnt/c/Program\ Files/qemu/qemu-system-i386.exe
CC = $(CROSS_CC_DIR)/i686-elf-gcc
ASM = nasm

LINKSCRIPT = $(SRC_DIR)/boot/linker.ld
KERNSOURCES_C := $(shell find $(SRC_DIR)/ -name *.c)
KERNSOURCES_ASM := $(shell find $(SRC_DIR)/ -name *.asm)
KERNOBJS := $(KERNSOURCES_C:%.c=%.o)  $(KERNSOURCES_ASM:%.asm=%.o)


#############################
# Make Targets              #
#############################

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	    -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
	    -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
	    -Wconversion -Wstrict-prototypes

LIBS = -lgcc
INCLUDES := -Ikernel
CFLAGS := -g -Wall -Wextra -std=gnu99 -ffreestanding -nostdlib $(INCLUDES) $(LIBS)
ASFLAGS := -f elf32
CPPFLAGS =


.PHONY: clean run
.SUFFIXES: .o .c .asm

asos.bin: $(KERNOBJS) $(LINKSCRIPT)
	@mkdir -p $(DEST_DIR)
	@$(CC) -T $(LINKSCRIPT) -o $(DEST_DIR)/$@ $(CFLAGS) $(KERNOBJS)
	@grub-file --is-x86-multiboot $(DEST_DIR)/$@

%.o : %.c
	@$(CC) -c $< -o $@ $(CFLAGS)

%.o : %.asm
	@$(ASM) $(ASFLAGS) $< -o $@ 

debug: asos.bin
	@$(QEMU) -s -S -kernel $(DEST_DIR)/asos.bin -no-reboot -monitor stdio

qemu: asos.bin
	@$(QEMU) -kernel $(DEST_DIR)/asos.bin -no-reboot  -monitor stdio

clean:
	@rm -rf $(DEST_DIR) $(ARCHOBJS) $(KERNOBJS)  $(shell find $(SRC_DIR)/ -name *.o)

print-%:
	@echo $* = $($*)

