CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: editor

editor: editor.c
	gcc $(CFLAGS) editor.c -o editor $(LDFLAGS)

clean:
	rm -f editor
