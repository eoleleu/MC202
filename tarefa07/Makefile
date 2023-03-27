CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: selecionar

selecionar: selecionar.c
	gcc $(CFLAGS) selecionar.c -o selecionar $(LDFLAGS)

clean:
	rm -f selecionar
