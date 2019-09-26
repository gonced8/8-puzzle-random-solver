CC = gcc
CFLAGS = -I$(LDIR) -Wall -ansi -pedantic -O3

.PHONY: all run clean

all:
	gcc ./main.c -Wall -pedantic -O3 -o main

run: all
	./main

clean:
	rm -rf main
