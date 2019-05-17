############################
# Defaultable flag options #
############################

ARCH ?= i686
CC_PREFIX ?= $(HOME)/Documents/cc
PREFIX ?= $(shell pwd)
DEST_DIR ?= $(PREFIX)/bin
BUILD_DIR ?= $(PREFIX)/build

###############################################
# Flags and Architecture Specific Variables   #
###############################################

CFLAGS = -g -Wall -Wextra -std=gnu99 -ffreestanding
CPPFLAGS =
LDFLAGS =
LIBS = -lgcc

CC = $(CC_PREFIX)/bin/i686-elf-gcc
ASM = $(CC_PREFIX)/bin/i686-elf-as
LINKSCRIPT = $(ARCHDIR)/linker.ld

ARCHDIR ?= $(PREFIX)/arch/$(ARCH)
OBJS := $(ARCHDIR)/boot.o $(ARCHDIR)/init_tables.o

#############################
# Make Targets              #
#############################

OBJS := $(OBJS) kernel/kernel.o kernel/tty.o kernel/segments.o
INCLUDES := -I$(PREFIX)/include
WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	    -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
	    -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
	    -Wconversion -Wstrict-prototypes

CFLAGS := $(CFLAGS) -nostdlib $(INCLUDES)


.PHONY: clean run
.SUFFIXES: .o .c .s

asos.bin: $(OBJS) $(LINKSCRIPT)
	@mkdir -p $(DEST_DIR)
	@$(CC) -T $(LINKSCRIPT) -o $(DEST_DIR)/$@ $(CFLAGS) $(OBJS)
	@grub-file --is-x86-multiboot $(DEST_DIR)/$@

%.o : %.c
	@$(CC) -c $< -o $@ $(CFLAGS)

%.o : %.s
	@$(ASM) $< -o $@

run: asos.bin
	@qemu-system-i386 -s -S -kernel $(DEST_DIR)/asos.bin -curses

qemu: asos.bin
	@qemu-system-i386 -s -S -kernel $(DEST_DIR)/asos.bin

clean:
	@rm -rf $(DEST_DIR) $(BUILD_DIR) $(OBJS) *.o */*.o */*/*.o

