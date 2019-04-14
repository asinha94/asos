############################
# Defaultable flag options #
############################

# Default architecture
ARCH ?= i686

# Direcotries
PREFIX ?= $(shell pwd)
DEST_DIR ?= $(PREFIX)/bin
BUILD_DIR ?= $(PREFIX)/build

############################
# Hardocded options        #
############################

CFLAGS = -g -Wall -Wextra -std=gnu99 -ffreestanding
CPPFLAGS =
LDFLAGS =
LIBS = -lgcc

############################
# Architecture Specific    #
############################

ARCHDIR ?= $(PREFIX)/arch/$(ARCH)
include $(ARCHDIR)/make.inc

CFLAGS := $(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS := $(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS := $(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS := $(LIBS) $(KERNEL_ARCH_LIBS)
OBJS := $(KERNEL_ARCH_OBJS)

CC = $(KERNEL_ARCH_CC)
ASM = $(KERNEL_ARCH_ASM)
LINKSCRIPT = $(KERNEL_ARCH_LINKSCRIPT)

#############################
# Make Targets              #
#############################

OBJS := $(OBJS) kernel/kernel.o arch/i686/tty.o arch/i686/vga.o 
INCLUDES := -I$(PREFIX)/include
CFLAGS := $(CFLAGS) -nostdlib $(INCLUDES)


.PHONY: clean run
.SUFFIXES: .o .c .s

asos.bin: $(OBJS) $(LINKSCRIPT)
	mkdir -p $(DEST_DIR)
	$(CC) -T $(LINKSCRIPT) -o $(DEST_DIR)/$@ $(CFLAGS) $(OBJS)
	grub-file --is-x86-multiboot $(DEST_DIR)/$@

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o : %.s
	$(ASM) $< -o $@

run: asos.bin
	qemu-system-i386 -s -S -kernel $(DESTDIR)/asos.bin -curses

qemu: asos.bin
	qemu-system-i386 -s -S -kernel $(DESTDIR)/asos.bin

clean:
	rm -rf $(DEST_DIR) $(BUILD_DIR) $(OBJS) *.o */*.o */*/*.o

