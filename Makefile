
PREFIX = $(shell pwd)
DEST_DIR = $(PREFIX)/bin
BUILD_DIR = $(PREFIX)/build
SRC_DIR = $(PREFIX)/kernel

CC = i686-elf-gcc
ASM = nasm

LINKSCRIPT = $(SRC_DIR)/linker.ld
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
.SUFFIXES: .o .c .S

asos.bin: $(KERNOBJS) $(LINKSCRIPT)
	@mkdir -p $(DEST_DIR)
	@$(CC) -T $(LINKSCRIPT) -o $(DEST_DIR)/$@ $(CFLAGS) $(KERNOBJS)
	@grub-file --is-x86-multiboot $(DEST_DIR)/$@

%.o : %.c
	@$(CC) -c $< -o $@ $(CFLAGS)

%.o : %.asm
	@$(ASM) $(ASFLAGS) $< -o $@ 

debug: asos.bin
	@qemu-system-i386 -s -S -kernel $(DEST_DIR)/asos.bin -curses

run-term: asos.bin
	@qemu-system-i386 -kernel $(DEST_DIR)/asos.bin -curses

qemu: asos.bin
	@qemu-system-i386 -kernel $(DEST_DIR)/asos.bin

clean:
	@rm -rf $(DEST_DIR) $(BUILD_DIR) $(ARCHOBJS) $(KERNOBJS) *.o */*.o */*/*.o */*/*/*.o

print-%:
	@echo $* = $($*)

