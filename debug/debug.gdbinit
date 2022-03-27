
# Start debugging
set disassembly-flavor intel
file ./build/asos.bin
target remote 172.30.128.1:1234
break kernel_main
continue
