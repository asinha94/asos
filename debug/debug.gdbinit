
# Start debugging
set disassembly-flavor intel
file ./build/asos.bin
target remote  172.22.64.1:1234
break kernel_main
continue
