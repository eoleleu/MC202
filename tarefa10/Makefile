CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: centros

centros: centros.c
	gcc $(CFLAGS) centros.c -o centros $(LDFLAGS)

clean:
	rm -f centros
