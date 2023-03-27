CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: otimizar calculadora

otimizar: otimizar.c
	gcc $(CFLAGS) otimizar.c -o otimizar $(LDFLAGS)

calculadora: calculadora.c
	gcc $(CFLAGS) calculadora.c -o calculadora $(LDFLAGS)

clean:
	rm -f otimizar calculadora
