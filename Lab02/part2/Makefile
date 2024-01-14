CC=clang

compile: half.c square.c twice.c
	$(CC) half.c -o half
	$(CC) square.c -o square
	$(CC) twice.c -o twice

all: compile clean

clean:
	rm half square twice

.PHONY: clean
