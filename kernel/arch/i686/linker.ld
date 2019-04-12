/* bootloader starts at this symbol */
ENTRY(_start)

SECTIONS
{
        /* Kernel and other sections start at 1MiB (Convention) */
        . = 1M;

        /* First 4KiB contains only the multiboot headers */
        .text BLOCK(4K) : ALIGN(4K)
        {
                *(.multiboot)
                *(.text)
        }

        /* read only data */
        .rodata BLOCK(4K) : ALIGN(4K)
        {
                *(.data)
        }

        /*rw data including the stack */
        .bss BLOCK(4K) : ALIGN(4K)
        {
                *(COMMON)
                *(.bss)
        }

}
