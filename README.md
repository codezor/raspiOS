# raspiOS

## Descriptions
Created a really small os for Rasberry Pi.

## TODO
Need to run this in ubuntu and set up a qemu for a rasberry pi emulator with an arm cpu.
Build to for compiling arm will be needed as well. 


build a qemu using the following 
```
qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel myos.elf
```

## Files 
boot.s
kernel.c 
linker.ld
Makefile
myos.elf

### References
https://jsandler18.github.io/
