# ASinhaOS

My pet project in bootstrapping a bare-bones OS. The goal is for this to eventually become a POSIX compliant OS

## Completed:
- [X] Boot into kernel code
- [X] Load GDT
- [X] Enable Protected mode with CR0 and verify
- [X] Create IDT

## Work to be completed
- [ ] Remap (A)PIC IRQ lines and create handlers
- [ ] Create PIT/RTC drivers
- [ ] Create kprintf for debugging
- [ ] Create keyboard handler
- [ ] Enabled Paging and move kernel to higher half?
- [ ] Configure VGA/VESA graphics

## Optional
- [ ] Use multiboot2
