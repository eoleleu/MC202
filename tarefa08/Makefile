CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: buscador

buscador: utils.h utils.c indice.h indice.c buscador.c
	gcc $(CFLAGS) utils.c indice.c buscador.c -o buscador $(LDFLAGS)

clean:
	rm -f buscador
