C_SRCs=$(wildcard kernel/*.c drivers/*.c libs/*.c apps/*.c)
HEADERS=$(wildcard kernel/*.h drivers/*.h libs/*.h apps/*.h)
OBJs=$(C_SRCs:.c=.o kernel/interrupts.o)
#cf. https://wiki.osdev.org/GCC_Cross-Compiler
CC=i386-elf-gcc#home made cross compiler
LD=i386-elf-ld#home made cross linker
GDB=i386-elf-gdb#home made cross debugger
C_FLAGS=-g -ffreestanding -O2 -pedantic -Wall -Wextra -std=c99

osImg.bin: bootloader/boot.bin kernel.bin
	cat $^ > osImg.bin

kernel.bin: bootloader/kernelEntry.o ${OBJs}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

#for debug
kernel.elf: bootloader/kernelEntry.o ${OBJs}
	${LD} -o $@ -Ttext 0x1000 $^

run: osImg.bin
	qemu-system-i386 -drive file=osImg.bin,format=raw,index=0,if=floppy

debug: osImg.bin kernel.elf
#it is a bit broken atm
	qemu-system-i386 -s -drive file=osImg.bin,format=raw,index=0,if=floppy -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} $(C_FLAGS) -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o osImg.bin *.elf
	rm -rf kernel/*.o bootloader/*.bin drivers/*.o bootloader/*.o libs/*.o