CC=clang
CFLAGS=--std=gnu11 -Wall -Wextra -Werror

all: chickenfuck

chickenfuck: main.c
	$(CC) $(CFLAGS) main.c -o chickenfuck

clean:
	rm chickenfuck
