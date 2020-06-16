
PREFIX = $(shell pwd)
BUILD_DIR = $(PREFIX)/build
BIN_DIR = $(PREFIX)/bin
SRC_DIR = $(PREFIX)/kernel
CC_VERSION = gcc-7.5.0
CROSS_CC_DIR = $(BIN_DIR)/$(CC_VERSION)/bin
ISODIR = $(BUILD_DIR)/isodir

QEMU = /mnt/c/Program\ Files/qemu/qemu-system-i386.exe
BOCHS = /mnt/c/Program\ Files/Bochs-2.6.11/bochs.exe
CC = $(CROSS_CC_DIR)/i686-elf-gcc
ASM = nasm

LINKSCRIPT = $(SRC_DIR)/boot/linker.ld
KERNSOURCES_C := $(shell find $(SRC_DIR)/ -name *.c)
KERNSOURCES_ASM := $(shell find $(SRC_DIR)/ -name *.asm)
KERNOBJS := $(KERNSOURCES_C:%.c=%.o)  $(KERNSOURCES_ASM:%.asm=%.o)

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	    -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
	    -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
	    -Wconversion -Wstrict-prototypes

LIBS = -lgcc
INCLUDES := -Ikernel
CFLAGS := -g -Wall -Wextra -std=gnu99 -ffreestanding -nostdlib $(INCLUDES) $(LIBS)
ASFLAGS := -f elf32 -g
CPPFLAGS =

#############################
# Make Targets              #
#############################

.PHONY: clean qemu-run
.SUFFIXES: .o .c .asm

asos.bin: $(KERNOBJS) $(LINKSCRIPT)
	@mkdir -p $(BUILD_DIR)
	@$(CC) -T $(LINKSCRIPT) -o $(BUILD_DIR)/$@ $(CFLAGS) $(KERNOBJS)
	@grub-file --is-x86-multiboot $(BUILD_DIR)/$@

%.o : %.c
	@$(CC) -c $< -o $@ $(CFLAGS)

%.o : %.asm
	@$(ASM) $(ASFLAGS) $< -o $@ 

qemu-dbg: asos.bin
	@$(QEMU) -s -S -kernel $(BUILD_DIR)/asos.bin -no-reboot -monitor stdio

qemu-run: asos.bin
	@$(QEMU) -kernel $(BUILD_DIR)/asos.bin -no-reboot  -monitor stdio

bochs-run: asos.bin
	@$(BOCHS)

gdb: asos.bin
	@gdb -x ./debug/debug.gdbinit

iso-dir: asos.bin
	@mkdir -p $(ISODIR)/boot/grub
	@cp $(BUILD_DIR)/asos.bin $(ISODIR)/boot
	@cp utils/grub.cfg $(ISODIR)/boot/grub
	@cp utils/stage2_eltorito $(ISODIR)/boot/grub

iso: iso-dir
	@grub-mkrescue -o $(BUILD_DIR)/asos.iso $(ISODIR)

# This shouldn't be necessary anymore
iso9660: iso-dir
	@mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot \
			 -boot-load-size 4 -boot-info-table \
			 -o $(BUILD_DIR)/asos9960.iso $(ISODIR)

clean:
	@rm -rf $(BUILD_DIR) $(KERNOBJS)

print-%:
	@echo $* = $($*)

