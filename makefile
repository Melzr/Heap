C=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
CVAL=--leak-check=full --track-origins=yes --show-reachable=yes

val: heap
	valgrind $(CVAL) ./heap

heap: heap.h heap.c pruebas.c
	$(CC) heap.c pruebas.c -o heap $(CFLAGS)

ejecutar: heap
	./heap

.PHONY: clean
clean:
	rm heap