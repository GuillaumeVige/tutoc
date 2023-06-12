# Link command:
#
tuto: tuto.o
	gcc -g tuto.o -o tuto.exe

# Compilation commands:
tuto.o: tuto.c
	gcc -g -c tuto.c -o tuto.o
