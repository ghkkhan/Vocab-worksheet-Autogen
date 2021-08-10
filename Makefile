SHELL = /bin/sh

CC=g++
CFLAGS=-Wall -Werror -c

all: vocab_gen

vocab_gen: main.o WSGen.o 
		$(CC) main.o WSGen.o -o vocab_gen

main.o: ./src/main.cpp
		$(CC) ./src/main.cpp $(CFLAGS)

WSGen.o: ./src/WSGen.cpp
		$(CC) ./src/WSGen.cpp $(CFLAGS)

clean:
		rm -rf *.o
clean_all:
		rm -rf *.o vocab_gen