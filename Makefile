SHELL = /bin/sh

CC=g++
CFLAGS=-Wall -Werror -c

all: vocab_gen

vocab_gen: vocab_gen.o Databank.o 
		$(CC) vocab_gen.o Databank.o -o vocab_gen

vocab_gen.o: ./src/vocab_gen.cpp
		$(CC) ./src/vocab_gen.cpp $(CFLAGS)

Databank.o: ./src/Databank.cpp
		$(CC) ./src/Databank.cpp $(CFLAGS)

clean:
		rm -rf *.o
clean_all:
		rm -rf *.o vocab_gen