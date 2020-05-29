
PREFIX = $(shell pwd)
DEST_DIR = $(PREFIX)/bin
BUILD_DIR = $(PREFIX)/build
SRC_DIR = $(PREFIX)/kernel

CC = i686-elf-gcc
ASM = i686-elf-as

LINKSCRIPT = $(SRC_DIR)/linker.ld
KERNSOURCES_C := $(shell find $(SRC_DIR)/ -name *.c)
KERNSOURCES_ASM := $(shell find $(SRC_DIR)/ -name *.S)
KERNOBJS_C := $(KERNSOURCES_C:%.c=%.o)
KERNOBJS_ASM:= $(KERNSOURCES_ASM:%.S=%.o)
#INCLUDES := -Ikernal

#############################
# Make Targets              #
#############################

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	    -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
	    -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
	    -Wconversion -Wstrict-prototypes

CFLAGS := -g -Wall -Wextra -std=gnu99 -ffreestanding -nostdlib #$(INCLUDES)
ASFLAGS := -msyntax=intel -mnaked-reg
CPPFLAGS =
LDFLAGS =
LIBS = -lgcc

.PHONY: clean run
.SUFFIXES: .o .c .S

asos.bin: $(KERNOBJS_C) $(KERNOBJS_ASM) $(LINKSCRIPT)
	@mkdir -p $(DEST_DIR)
	@$(CC) -T $(LINKSCRIPT) -o $(DEST_DIR)/$@ $(CFLAGS) $(ARCHOBJS) $(KERNOBJS_C) $(KERNOBJS_ASM)
	@grub-file --is-x86-multiboot $(DEST_DIR)/$@

%.o : %.c
	@$(CC) -c $< -o $@ $(CFLAGS)

%.o : %.S
	@$(ASM) $< -o $@ $(ASFLAGS)

debug: asos.bin
	@qemu-system-i386 -s -S -kernel $(DEST_DIR)/asos.bin -curses

run: asos.bin
	@qemu-system-i386 -S -kernel $(DEST_DIR)/asos.bin -curses

qemu: asos.bin
	@qemu-system-i386 -s -S -kernel $(DEST_DIR)/asos.bin

clean:
	@rm -rf $(DEST_DIR) $(BUILD_DIR) $(ARCHOBJS) $(KERNOBJS) *.o */*.o */*/*.o

print-%:
	@echo $* = $($*)

