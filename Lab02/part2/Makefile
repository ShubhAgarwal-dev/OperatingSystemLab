CC=clang

make: compile

half:
	$(CC) -std=c11 half.c -o half

square:
	$(CC) -std=c11 square.c -o square

twice:
	$(CC) -std=c11 twice.c -o twice

compile: half square twice

all: compile

clean:
	rm half square twice

.PHONY: clean
