############################
# Defaultable flag options #
############################

# Compiling and linker options
CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

# Default architecture
ARCH?=i686

# Direcotries
PREFIX?=$(shell pwd)
DESTDIR?=$(PREFIX)/build

############################
# Hardocded options        #
############################

CFLAGS:=$(CFLAGS) -Wall -Wextra -std=gnu99 -ffreestanding
CPPFLAGS:=$(CPPFLAGS)
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -lgcc

############################
# Architecture Specific    #
############################

ARCHDIR?=$(PREFIX)/arch/$(ARCH)
include $(ARCHDIR)/make.inc

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS = $(KERNEL_ARCH_OBJS) \
	          kernel/kernel.o

CC=$(KERNEL_ARCH_CC)
ASM=$(KERNEL_ARCH_ASM)
LINKSCRIPT=$(KERNEL_ARCH_LINKSCRIPT)

#############################
# Make Targets              #
#############################

OBJS=$(KERNEL_OBJS)
CFLAGS:=$(CFLAGS) -nostdlib

.PHONY: clean run
.SUFFIXES: .o .c .s

asos.bin: $(OBJS) $(LINKSCRIPT)
	mkdir -p $(DESTDIR)
	$(CC) -T $(LINKSCRIPT) -o $(DESTDIR)/$@ $(CFLAGS) $(OBJS)
	grub-file --is-x86-multiboot $(DESTDIR)/$@

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o : %.s
	$(ASM) $< -o $@

run: asos.bin qemu

qemu:
	qemu-system-i386 -kernel $(DESTDIR)/asos.bin

clean:
	rm -rf $(DESTDIR)
	rm -f $(OBJS) *.o */*.o */*/*.o
