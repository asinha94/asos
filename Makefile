
# Directories
PREFIX       = $(shell pwd)
BUILD_DIR    = $(PREFIX)/build
BIN_DIR      = $(PREFIX)/bin
SRC_DIR      = $(PREFIX)/kernel
CC_VERSION   = gcc-7.5.0
CROSS_CC_DIR = $(BIN_DIR)/$(CC_VERSION)/bin
ISODIR       = $(BUILD_DIR)/isodir
WIN_ISO_DIR  = /mnt/c/Users/Anura/Downloads
WIN_ISO_PATH = C:\Users\Anura\Downloads
POWERSHELL   = powershell.exe -Command

# Compiler & Build
CC   = $(CROSS_CC_DIR)/i686-elf-gcc
CPP  = $(CROSS_CC_DIR)/i686-elf-g++
GAS  = $(CROSS_CC_DIR)/i686-elf-as
NASM = nasm


# Emulators
QEMU      = /mnt/c/Program\ Files/qemu/qemu-system-i386.exe
QEMU_TERM = /usr/bin/qemu-system-i386
QEMU_WIN  = 'C:\Program Files\qemu\qemu-system-i386.exe'
BOCHS     = /mnt/c/Program\ Files/Bochs-2.6.11/bochs.exe
BOCHSDBG  = /mnt/c/Program\ Files/Bochs-2.6.11/bochsdbg.exe


# Files
LINKSCRIPT          = $(SRC_DIR)/boot/linker.ld
KERNSRCS_CPP       := $(shell find $(SRC_DIR)/ -name *.cpp)
KERNSRCS_ASM_INTEL := $(shell find $(SRC_DIR)/ -name *.asm)
KERNSRCS_ASM_ATT   := $(shell find $(SRC_DIR)/ -name *.S)
CRTBEGIN_OBJ       := $(shell $(CPP) $(CPPFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ         := $(shell $(CPP) $(CPPFLAGS) -print-file-name=crtend.o)
KERNOBJS           := $(KERNSRCS_CPP:%.cpp=%.o)  $(KERNSRCS_ASM_INTEL:%.asm=%.o) $(KERNSRCS_ASM_ATT:%.S=%.o)


WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	        -Wwrite-strings -Wcast-qual -Wconversion -Wno-long-long \
	        -Wredundant-decls -Winline  -Wno-sign-conversion -Wno-conversion\
	     
LIBS      = -lgcc
INCLUDES := -Ikernel
ASFLAGS  := -f elf32 -g
CFLAGS   := -g $(WARNINGS) -std=gnu99 -ffreestanding -nostdlib -masm=intel $(INCLUDES) $(LIBS)
CPPFLAGS := -g $(WARNINGS) -std=c++17 -ffreestanding -nostdlib -masm=intel -fno-exceptions -fno-rtti  $(INCLUDES) $(LIBS)




#############################
# Make Targets              #
#############################

.PHONY: clean
.SUFFIXES: .o .cpp .asm .S

asos.bin: $(KERNOBJS) $(LINKSCRIPT)
	@mkdir -p $(BUILD_DIR)
	@$(CPP) -T $(LINKSCRIPT) -o $(BUILD_DIR)/$@ $(CPPFLAGS) $(KERNOBJS) $(CRTBEGIN_OBJ) $(CRTEND_OBJ)
	@grub-file --is-x86-multiboot $(BUILD_DIR)/$@

%.o : %.cpp
	@$(CPP) -c $< -o $@ $(CPPFLAGS)

%.o : %.asm
	@$(NASM) $(ASFLAGS) $< -o $@

%.o : %.S
	@$(GAS) $< -o $@

iso-dir: asos.bin
	@mkdir -p $(ISODIR)/boot/grub
	@cp $(BUILD_DIR)/asos.bin $(ISODIR)/boot
	@cp utils/grub.cfg $(ISODIR)/boot/grub

iso: iso-dir
	@grub-mkrescue -o $(BUILD_DIR)/asos.iso $(ISODIR)

qemu-dbg: iso
	@cp $(BUILD_DIR)/asos.iso $(WIN_ISO_DIR)
	@$(POWERSHELL) "& $(QEMU_WIN) -s -S -no-reboot -serial stdio -cdrom $(WIN_ISO_PATH)/asos.iso"

qemu: iso
	@cp $(BUILD_DIR)/asos.iso $(WIN_ISO_DIR)
	@$(POWERSHELL) "& $(QEMU_WIN) -no-reboot -vga std -monitor stdio -serial stdio -cdrom $(WIN_ISO_PATH)/asos.iso"

bochs: iso
	@$(BOCHS) -f bochsrc.cd -q

bochs-dbg: iso
	@$(BOCHSDBG) -f bochsrc.cd -q

gdb: asos.bin
	@gdb -x ./debug/debug.gdbinit

clean:
	@rm -rf $(BUILD_DIR) $(KERNOBJS) $(WIN_ISO_DIR)/asos.iso serial.log

print-%:
	@echo $* = $($*)

