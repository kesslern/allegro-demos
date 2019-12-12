NAME=allegro-test
CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lallegro_main -lallegro -lallegro_primitives
DEBUG=-g -DDEBUG

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=$(NAME).out

all: $(SOURCES) $(EXECUTABLE)

debug: CFLAGS += $(DEBUG)
debug: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
