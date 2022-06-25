
# Start debugging
set disassembly-flavor intel
file ./build/asos.bin
target remote 172.27.208.1:1234
break kernel_main
continue
