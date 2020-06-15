
; Output byte to port
global outportb
outportb:
    mov dx, [esp + 4] ; port
    mov al, [esp + 8] ; copy byte data
    out dx, al


; Grab byte from port
global inportb
inportb:
    mov dx, [esp + 4] ; port
    in al, dx ; put byte in ax


global io_wait
io_wait:
    ret ; not really needed on modern PCs


global disable_interrupts 
disable_interrupts:
    cli


global enable_interrupts
enable_interrupts:
    sti