
# Start debugging
set disassembly-flavor intel
file ./bin/asos.bin
target remote localhost:1234
break kernel_main
continue
