
# Start debugging
set disassembly-flavor intel
file ./build/asos.bin
target remote localhost:1234
break kernel_main
continue
