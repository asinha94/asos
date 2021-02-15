
# Directories
PREFIX = $(shell pwd)
BUILD_DIR = $(PREFIX)/build
BIN_DIR = $(PREFIX)/bin
SRC_DIR = $(PREFIX)/kernel
CC_VERSION = gcc-7.5.0
CROSS_CC_DIR = $(BIN_DIR)/$(CC_VERSION)/bin
ISODIR = $(BUILD_DIR)/isodir

# Compiler & Build
CC = $(CROSS_CC_DIR)/i686-elf-gcc
ASM = nasm

# Emulators
QEMU_TERM = /usr/bin/qemu-system-i386
QEMU = /mnt/c/Program\ Files/qemu/qemu-system-i386.exe
BOCHS = /mnt/c/Program\ Files/Bochs-2.6.11/bochs.exe
BOCHSDBG = /mnt/c/Program\ Files/Bochs-2.6.11/bochsdbg.exe


# Files
LINKSCRIPT = $(SRC_DIR)/boot/linker.ld
KERNSOURCES_C := $(shell find $(SRC_DIR)/ -name *.c)
KERNSOURCES_ASM := $(shell find $(SRC_DIR)/ -name *.asm)
KERNOBJS := $(KERNSOURCES_C:%.c=%.o)  $(KERNSOURCES_ASM:%.asm=%.o)

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	        -Wwrite-strings -Wcast-qual -Wconversion -Wno-long-long \
	        -Wredundant-decls -Wnested-externs -Winline  -Wno-sign-conversion -Wno-conversion\
	     
LIBS = -lgcc
INCLUDES := -Ikernel
CFLAGS := -g $(WARNINGS) -std=gnu99 -ffreestanding -nostdlib -masm=intel $(INCLUDES) $(LIBS)
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
	@grub-file --is-x86-multiboot2 $(BUILD_DIR)/$@

%.o : %.c
	@$(CC) -c $< -o $@ $(CFLAGS)

%.o : %.asm
	@$(ASM) $(ASFLAGS) $< -o $@

iso-dir: asos.bin
	@mkdir -p $(ISODIR)/boot/grub
	@cp $(BUILD_DIR)/asos.bin $(ISODIR)/boot
	@cp utils/grub.cfg $(ISODIR)/boot/grub
	@cp utils/stage2_eltorito $(ISODIR)/boot/grub
	@objcopy --only-keep-debug $(BUILD_DIR)/asos.bin $(BUILD_DIR)/asos.sym
	@nm $(BUILD_DIR)/asos.sym | grep " T " | awk '{ print $$1 " " $$3 }' > $(BUILD_DIR)/bochs.sym

iso: iso-dir
	@grub-mkrescue -o $(BUILD_DIR)/asos.iso $(ISODIR)

# This shouldn't be necessary anymore
iso9660: iso-dir
	@mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot \
			 -boot-load-size 4 -boot-info-table \
			 -o $(BUILD_DIR)/asos9960.iso $(ISODIR) 

qemu-termdbg: iso
	@$(QEMU_TERM) -s -S -cdrom $(BUILD_DIR)/asos.iso -no-reboot -curses

qemu-dbg: iso
	@$(QEMU) -s -S -cdrom $(BUILD_DIR)/asos.iso -no-reboot -monitor stdio

qemu-run: iso
	@$(QEMU) -cdrom $(BUILD_DIR)/asos.iso -no-reboot -monitor stdio

bochs-run: iso
	@$(BOCHS) -f bochsrc.cd -q

bochs-dbg: iso
	@$(BOCHSDBG) -f bochsrc.cd -q

gdb: asos.bin
	@gdb -x ./debug/debug.gdbinit

clean:
	@rm -rf $(BUILD_DIR) $(KERNOBJS)

print-%:
	@echo $* = $($*)

