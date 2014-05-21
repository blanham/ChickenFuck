CC=clang
CFLAGS=--std=gnu11

all: chickenfuck

chickenfuck: main.c
	$(CC) $(CFLAGS) main.c -o chickenfuck
