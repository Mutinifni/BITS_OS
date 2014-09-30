dd if=kernel.bin of=kernel.img bs=512 count=1 $(REDIRECT) 
dd if=/dev/zero of=kernel.img skip=1 seek=1 bs=512 count=2879 > /dev/null 2>&1