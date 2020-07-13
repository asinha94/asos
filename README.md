# ASinhaOS

My pet project in bootstrapping a bare-bones OS. The goal is for this to eventually become a POSIX compliant OS

## Completed:
- [X] Boot intp Protected Mode C Kernel
- [X] Interrupt driven kernel architecture
- [X] Partial driver support (keyboard)

## Short-Term Work
- [ ] Create handler for interrupt 0-31
- [ ] High-half kernel and paging
- [ ] Move the blinking cursor
- [ ] Create PIT/RTC drivers

## Long-Term Work
- [ ] Process Scheduling
- [ ] File-system support (FAT initially)  
- [ ] Basic syscalls (read/write/fork/exec)
- [ ] bash (or variant) shell

## Optional
- [ ] Use APIC instead of PIC
- [ ] Use multiboot2


## Resources
None of this would be possible without the amazing information from these sources

- wiki.osdev.org
- http://www.osdever.net/tutorials/
- https://github.com/cfenollosa/os-tutorial