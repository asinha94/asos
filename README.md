# ASinhaOS

My pet project in bootstrapping a bare-bones OS. The goal is for this to eventually become a POSIX compliant OS

## Completed:
- [X] Enable Protected Mode
- [X] Boot into C kernel
- [X] Create GDT
- [X] Create IDT
- [X] Create kprintf for debugging
- [X] Create software interrupt

## Short-Term Work
- [ ] Create keyboard handler
- [ ] Create handler for interrupt 0-31
- [ ] High-half kernel
- [ ] Enable paging
- [ ] Move the blinking cursor
- [ ] Create PIT/RTC drivers

## Long-Term Work
- [ ] Process Scheduling
- [ ] File-system support (FAT initially)  

## Optional
- [ ] Use APIC instead of PIC
- [ ] Use multiboot2


## Resources
None of this would be possible without the amazing information from these sources

- wiki.osdev.org
- http://www.osdever.net/tutorials/
- https://github.com/cfenollosa/os-tutorial