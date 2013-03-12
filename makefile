all:
	nasm context.asm -f elf64 -o context.o && gcc main.c threads.c context.o -g -O0 && ./a.out
