# asOS

My pet project in bootstrapping a bare-bones OS. The goal is for this to eventually become a POSIX compliant OS

---



## Completed:
- [X] Boot intp Protected Mode C Kernel
- [X] Interrupt driven kernel architecture
- [X] Partial driver support (keyboard)
- [x] High-half kernel and paging support
- [x] Kernel Malloc implementation

## Short-Term Work
- [ ] Use multiboot2 (Memory Map)
- [ ] Improve keyboard handler
- [ ] Create handlers for interrupt 0-31
- [ ] Handle exceptions (beyond just logging)
- [ ] Create PIT/RTC drivers
- [ ] Improve malloc to use slab allocation
- [ ] Use buddy allocator for PMM
- [ ] Move the blinking cursor
- [ ] Use APIC instead of PIC

## Long-Term Work
- [ ] bash (or variant) shell
- [ ] Process Scheduling
- [ ] File-system support (FAT/ext2/ntfs?)  
- [ ] Basic syscalls (read/write/fork/exec/mmap)
- [ ] TCP/IP networking stack
- [ ] Minimal Windowing/Graphics

## Optional
- [ ] 64-bit
- [ ] UEFI

--- 
## Development

Development takes place on a *nix environment, preferably linux. WSL works too.

### Cross-compiler
In order to develop asOS you will need a cross-compiler. You can find detailed instructions on how to build your cross-compiler (preferably GCC) from [wiki.osdev.org](https://wiki.osdev.org/Why_do_I_need_a_Cross_Compiler%3F). Alternatively I have pre-compiled and packaged the necessary binary tools on the [releases page](https://github.com/asinha94/asos/releases/tag/v0.0.1).

Once you have the cross-compiler successfully built and installed, you will need to modify the project makefile to point to the appropriate directory.
The `$(CROSS_CC_DIR)` var should point to the bin directory of the cross-compiler.

### Other programs

You will need the following programs as well
- nasm
- grub2
- gdb
- bochs/qemu
- [xorriso](http://www.gnu.org/software/xorriso/#download) (optional)
- VSCode (optional)

## Running asOS

The best way for you to run the asOS is to run the generated ISO in your VM of choice. I have currently tested this on both QEMU and Bochs. Once the build system is in place the `make` commands can both build and run the OS.

Set the path of the qemu/bochs executable in the makefile. If you are using WSL you can use the windows .exe and Windows will figure out how to call it. Then you can run with `make bochs-run` or `make qemu-run`.

## Debugging

Both Bochs and QEMU can be used to debug. Assuming either tool is installed and configured in the makefile, all you have to do is call either of 

- `make qemu-dbg`
- `make bochs-dbg`. 

### QEMU
When using qemu-dbg, the os will be paused waiting for GDB or another interface to continue execution. You can connect to qemu through GDB on port `1234`, then execute as normal. QEMU debugging is useful for stepping through the code to check your application logic while Bochs is useful.


### Bochs
Bochs debugging is useful when debugging hardware i.e making sure your CPU is in the correct state, exceptions are being handled, investigate triple-faults etc... It has it's own built in debugger which is similar to GDB, but not 100% compatible.

---

## Resources/References

- wiki.osdev.org
- http://www.osdever.net/tutorials/
- https://github.com/cfenollosa/os-tutorial