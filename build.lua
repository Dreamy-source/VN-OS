os.execute("clear")
while true do
    print("1. run")
    print("2. build")
    print("3. run & debug")
    local input = tonumber(io.read())

    if input == 1 then
        os.execute([[
            clear
            nasm -f bin boot.asm -o bin/boot.bin
            nasm -f elf32 kernel.asm -o bin/kernel_asm.o
            gcc -m32 -ffreestanding -fno-pie -fno-stack-protector -c kernel.c -o bin/kernel_c.o
            ld -m elf_i386 -Ttext 0x9000 -o bin/kernel.bin bin/kernel_asm.o bin/kernel_c.o --oformat binary
            cat bin/boot.bin bin/kernel.bin > bin/vanilla.bin
            qemu-system-x86_64 -audiodev pa,id=audio0 -machine pcspk-audiodev=audio0 -drive format=raw,file=bin/vanilla.bin
        ]])
    end
    if input == 2 then
        os.execute([[
            clear
            nasm -f bin boot.asm -o bin/boot.bin
            nasm -f elf32 kernel.asm -o bin/kernel_asm.o
            gcc -m32 -ffreestanding -fno-pie -fno-stack-protector -c kernel.c -o bin/kernel_c.o
            ld -m elf_i386 -Ttext 0x9000 -o bin/kernel.bin bin/kernel_asm.o bin/kernel_c.o --oformat binary
            cat bin/boot.bin bin/kernel.bin > bin/vanilla.bin
        ]])
    end
    if input == 3 then
        os.execute([[
            clear
            nasm -f bin boot.asm -o bin/boot.bin
            nasm -f elf32 kernel.asm -o bin/kernel_asm.o
            gcc -m32 -ffreestanding -fno-pie -fno-stack-protector -c kernel.c -o bin/kernel_c.o
            ld -m elf_i386 -Ttext 0x9000 -o bin/kernel.bin bin/kernel_asm.o bin/kernel_c.o --oformat binary
            cat bin/boot.bin bin/kernel.bin > bin/vanilla.bin
            qemu-system-x86_64 -audiodev pa,id=audio0 -machine pcspk-audiodev=audio0 -drive format=raw,file=bin/vanilla.bin -d int
        ]])
    end
end