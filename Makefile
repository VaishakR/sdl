# Makefile for SDL2 Test

# Compiler and flags
CC = g++
CFLAGS = -Wall
LDFLAGS = -lSDL2 -lSDL2_image

# Targets
TARGET = main
SOURCES = main.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(TARGET)
