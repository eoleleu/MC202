CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: matrioscas

matrioscas: matrioscas.c
	gcc $(CFLAGS) matrioscas.c -o matrioscas $(LDFLAGS)

clean:
	rm -f matrioscas
