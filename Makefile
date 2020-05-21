
PREFIX = $(shell pwd)
DEST_DIR = $(PREFIX)/bin
BUILD_DIR = $(PREFIX)/build
SRC_DIR = $(PREFIX)/kernel

CC = i686-elf-gcc
ASM = i686-elf-as

LINKSCRIPT = $(SRC_DIR)/linker.ld
ARCHOBJS := $(SRC_DIR)/boot.o $(SRC_DIR)/init_tables.o
KERNSOURCES := $(shell find $(SRC_DIR)/ -name *.c)
KERNOBJS := $(KERNSOURCES:%.c=%.o)
INCLUDES := -Ikernal

#############################
# Make Targets              #
#############################

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	    -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
	    -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
	    -Wconversion -Wstrict-prototypes

CFLAGS := -g -Wall -Wextra -std=gnu99 -ffreestanding -nostdlib $(INCLUDES)
CPPFLAGS =
LDFLAGS =
LIBS = -lgcc

.PHONY: clean run
.SUFFIXES: .o .c .s

asos.bin: $(KERNOBJS) $(LINKSCRIPT)
	@mkdir -p $(DEST_DIR)
	@$(ASM) $(SRC_DIR)/boot.s -o $(SRC_DIR)/boot.o
	@$(ASM) $(SRC_DIR)/init_tables.s -o $(SRC_DIR)/init_tables.o
	@$(CC) -T $(LINKSCRIPT) -o $(DEST_DIR)/$@ $(CFLAGS) $(ARCHOBJS) $(KERNOBJS)
	@grub-file --is-x86-multiboot $(DEST_DIR)/$@

%.o : %.c
	@$(CC) -c $< -o $@ $(CFLAGS)

run: asos.bin
	@qemu-system-i386 -s -S -kernel $(DEST_DIR)/asos.bin -curses

qemu: asos.bin
	@qemu-system-i386 -s -S -kernel $(DEST_DIR)/asos.bin

clean:
	@rm -rf $(DEST_DIR) $(BUILD_DIR) $(ARCHOBJS) $(KERNOBJS) *.o */*.o */*/*.o

print-%:
	@echo $* = $($*)

