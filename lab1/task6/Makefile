CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
INCLUDE = -Iinclude
SOURCES = src/functions.c src/validate.c main.c
TARGET = main.out

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCES) -o $(TARGET) -lm

clean:
	rm -f $(TARGET)

.PHONY: clean