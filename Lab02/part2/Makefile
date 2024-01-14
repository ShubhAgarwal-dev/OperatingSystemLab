CC=clang

compile: half.c square.c twice.c
	$(CC) -std=c11 half.c -o half
	$(CC) -std=c11 square.c -o square
	$(CC) -std=c11 twice.c -o twice

all: compile clean

clean:
	rm half square twice

.PHONY: clean
