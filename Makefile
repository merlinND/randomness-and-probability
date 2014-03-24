# Libs
LIB_SYS = -lm

# Compilation Binaries
CC = gcc
CFLAGS = -DDEBUG -g -Wall
LNFLAGS = $(LIB_SYS)

# Exe Sources
EXE_SRC = simple_output.c csv_output.c monobit_frequency.c run_length.c law_simulations.c mm1.c

# Other Sources
SRC = old_c_rand.c aes.c mersenne_twister.c von_neumann.c tools.c distributions.c queues.c

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
	echo "Oldrand 4 MSBs,Oldrand 4 LSBs,Von-Neumann,Mesrene-Twister,AES" > data/monobit.csv
	cat data/monobit.csv > data/runs.csv
	i=1 ; while [[ $$i -le 20 ]] ; do \
	./build/bin/csv_output > "data/rands_$$i.csv" ; \
	./build/bin/monobit_frequency >> "data/monobit.csv" ; \
	./build/bin/run_length >> "data/runs.csv" ; \
	((i = i + 1)) ; \
	done
	./build/bin/mm1

build/$(EXE): $(OBJECTS)
	$(CC) -o $@ $^ $(LNFLAGS)

# Patterns
build/%.o: src/%.c
	mkdir -p `dirname $@`
	$(CC) -c $(CFLAGS) -o $@ $<

build/bin/%: build/%.o $(OBJECTS)
	mkdir -p `dirname $@`
	$(CC) -o $@ $^ $(LNFLAGS)
