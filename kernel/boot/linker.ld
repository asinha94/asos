/* bootloader starts at this symbol */
ENTRY(_start)

SECTIONS
{
        /* Kernel by convention will be mapped at 3GB + 1MB */
        KERNEL_VA_OFFSET = 0xC0000000;
        . = 0xC0100000;
        _kernel_start = .;
        
        .text ALIGN(4K) : AT( ADDR(.text) - KERNEL_VA_OFFSET)
        {
                *(.multiboot)
                *(.text)
        }
        .rodata ALIGN(4K) : AT( ADDR(.rodata) - KERNEL_VA_OFFSET)
        {
                *(.rodata)
        }
        .data ALIGN(4K) : AT( ADDR(.data) - KERNEL_VA_OFFSET)
        {
                *(.data)
        }
        .bss ALIGN(4K) : AT( ADDR(.bss) - KERNEL_VA_OFFSET)
        {
                *(COMMON)
                *(.bss)
        }

        _kernel_end = .;
}
