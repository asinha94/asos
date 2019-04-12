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

CFLAGS:=$(CFLAGS) -Wall -Wextra -ffreestanding -std=gnu99
CPPFLAGS:=$(CPPFLAGS)
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS)

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
LINKSCRIPT=$(KERNEL_ARCH_LINKSCRIPT)

#############################
# Make Targets              #
#############################

OBJS=$(KERNEL_OBJS)

.PHONY: all clean
.SUFFIXES: .o .c .s
all: asos.bin

asos.bin: $(OBJS) $(LINKSCRIPT)
	mkdir -p $(DESTDIR)
	$(CC) -T $(LINKSCRIPT) -o $(DESTDIR)/$@ $(CFLAGS) $(OBJS)
	grub-file --is-x86-multiboot $(DESTDIR)/$@

%.o : %.c:
	$(CC) -c $< $@ $(CFLAGS)

%.o : %.s:
	$(CC) -c $< $@ $(CFLAGS)

clean:
	rm -rf $(DESTDIR)
	rm -f $(OBJS) *.o */*.o */*/*.o
