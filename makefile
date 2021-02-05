CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
OUTPUT=aventura
DEPENDENCIES=$(shell pwd)/$(shell find . -name '*.c')
ENTRY=main.c

all: $(OUTPUT) valgrind

aventura: $(DEPENDENCIES) $(ENTRY)
	gcc $(DEPENDENCIES) $(CFLAGS) -o $(OUTPUT)

valgrind: $(OUTPUT)
	valgrind $(VFLAGS) ./$(OUTPUT)

debug: $(OUTPUT)
	gdb -tui ./$(OUTPUT)
