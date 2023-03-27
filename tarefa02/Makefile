CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: classificar consultas

classificar: classificar.c
	gcc $(CFLAGS) classificar.c -o classificar $(LDFLAGS)

consultas: consultas.c
	gcc $(CFLAGS) consultas.c -o consultas $(LDFLAGS)

clean:
	rm -f classificar consultas
