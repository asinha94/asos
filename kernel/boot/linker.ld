/* bootloader starts at this symbol */
ENTRY(_start)

SECTIONS
{
        /* Load Multiboot headers after 1MiB */
        . = 0x00100000;
        /*.multiboot :
        {
                *(.multiboot)
        }*/

        /* Kernel by convention will be mapped at 3GiB + 1MiB
        /* i.e 3GiB past where it actuall will be. The linker
        /* doesn't actually put the kernel at that spot
        /* This is only done so the compiler uses the virtual memory offsets */
        kernel_va_offset = 0xC0000000;
        . = 0xC0100000;
        _kernel_start = .;

        .text ALIGN(4K) : AT( ADDR(.text) - kernel_va_offset)
        {
                *(.multiboot)
                *(.text)
        }
        .rodata ALIGN(4K) : AT( ADDR(.rodata) - kernel_va_offset)
        {
                *(.rodata)
        }
        .data ALIGN(4K) : AT( ADDR(.data) - kernel_va_offset)
        {
                *(.data)
        }
        .bss ALIGN(4K) : AT( ADDR(.bss) - kernel_va_offset)
        {
                *(COMMON)
                *(.bss)
        }
        _kernel_end = .;

}
