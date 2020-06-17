
; Output byte to port
global outport8
outport8:
    mov dx, [esp + 4] ; port
    mov al, [esp + 8] ; copy byte data
    out dx, al
    ret


; Grab byte from port
global inport8
inport8:
    mov dx, [esp + 4] ; port
    in al, dx ; put byte in ax
    ret


global disable_interrupts 
disable_interrupts:
    cli
    ret


global enable_interrupts
enable_interrupts:
    sti
    ret