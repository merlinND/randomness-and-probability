# Libs
LIB_SYS = -lm

# Compilation Binaries
CC = gcc
CFLAGS = -DDEBUG -g -Wall -std=c99
LNFLAGS = $(LIB_SYS)

# Exe Sources
EXE_SRC = final.c

# Other Sources
SRC = old_c_rand.c aes.c mersenne_twister.c von_neumann.c tools.c distributions.c queues.c tests.c

# Objets
OBJECTS = $(SRC:%.c=build/%.o)
EXE_OBJS = $(EXE_SRC:%.c=build/bin/%)

# Phony targets
.PHONY: clean run

# Rules
all: $(EXE_OBJS)

clean:
	rm -rf build/

run: $(EXE_OBJS)
	mkdir -p data
	build/bin/final > data/report.md
	cat data/report.md


build/$(EXE): $(OBJECTS)
	$(CC) -o $@ $^ $(LNFLAGS)

# Patterns
build/%.o: src/%.c
	mkdir -p `dirname $@`
	$(CC) -c $(CFLAGS) -o $@ $<

build/bin/%: build/%.o $(OBJECTS)
	mkdir -p `dirname $@`
	$(CC) -o $@ $^ $(LNFLAGS)
