# Libs
LIB_SYS = -lm

# Compilation Binaries
CC = gcc
CFLAGS = -DDEBUG -g -Wall
LNFLAGS = $(LIB_SYS)

# Exe Name
EXE = simu

# Sources
SRC = aes.c mersenne_twister.c von_neumann.c main_debut.c

# Objets
OBJECTS = $(SRC:%.c=build/%.o)

# Phony targets
.PHONY: clean run

# Rules
all: build/$(EXE)

clean:
	rm -rf build/

run: build/$(EXE)
	cd build; ./$(EXE)

build/$(EXE): $(OBJECTS)
	$(CC) -o $@ $^ $(LNFLAGS)

# Patterns
build/%.o: src/%.c
	mkdir -p `dirname $@`
	$(CC) -c $(CFLAGS) -o $@ $<
