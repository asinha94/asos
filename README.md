# asOS

My pet project in bootstrapping a bare-bones OS. The goal is for this to eventually become a POSIX compliant OS

![](asos.gif)

---

## Completed:
- [X] Boot intp Protected Mode C Kernel
- [X] Interrupt driven kernel architecture
- [X] Partial driver support (keyboard)
- [x] High-half kernel with paging enabled
- [x] Kernel Malloc implementation

## Short-Term Work
- [ ] Convert graphics stack to C++
- [ ] Remove global arrays. Convert some stuff to classes
- [ ] Figure out why ESC causes Page Fault
- [ ] Convert MM stuff to C++
- [ ] Create PIT/RTC drivers
- [ ] Create handlers for interrupt 0-31
- [ ] Handle exceptions (beyond just logging)
- [ ] Process Scheduling/Multitasking
- [ ] Jump to userspace
- [ ] Basic syscalls (read/write/fork/exec/mmap)
- [ ] Create char devices (i.e kbm for UI)
- [ ] Bash shell

## Long-Term Work
- [ ] Use APIC instead of PIC
- [ ] Improve malloc to use slab allocation
- [ ] Use buddy allocator for PMM (use stack instead of Bitmap)

- [ ] Basic Windowing Graphics 
- [ ] File-system support (FAT/ext2/ntfs?)  
- [ ] TCP/IP networking stack

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

Because I develop on VSCode (inside WSL2), while QEMU is running on Windows (to make use of the graphical environment) we are subject to [this bug](https://github.com/microsoft/WSL/issues/5298) where we cannot access localhost on the Windows side of things through WSL. To fix this you can do any of the below steps

1. Restart wsl with `wsl --shutdown` in powershell
2. find the Windows IP with `ipconfig` in powershell (search for `Ethernet adapter vEthernet (WSL)`)  and use that instead of localhost
3. Edit `/etc/hosts` in WSL2 by removing the IPv4 entry for `localhost` and add `localhost` to the IPv6 entry.
4. Run qemu inside WSL with `make qemu-termdbg`. This limits you to the console though

### Bochs
Bochs debugging is useful when debugging hardware i.e making sure your CPU is in the correct state, exceptions are being handled, investigate triple-faults etc... It has it's own built in debugger which is similar to GDB, but not 100% compatible.

---

## Resources/References

- [wiki.osdev.org](wiki.osdev.org)
- http://www.osdever.net/tutorials/
- https://github.com/cfenollosa/os-tutorial
