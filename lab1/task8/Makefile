CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
INCLUDE = -Iinclude
SOURCES = main.c src/converse.c src/validate.c
TARGET = main.out

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) *.tmp

.PHONY: clean test