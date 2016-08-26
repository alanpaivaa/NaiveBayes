LIBS = -lm
CC=gcc
CFLAGS=-Wno
SOURCES=main.c training.c csv.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all: main run
	$(CC) $(SOURCES) -o $(EXECUTABLE) $(LIBS)
	
run:main
	./main