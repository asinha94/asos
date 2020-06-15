
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
    in ax, dx ; put byte in ax

global io_wait
io_wait:
    ret ; not really needed on modern PCs