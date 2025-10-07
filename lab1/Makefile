CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror
INCLUDE = -Iinclude
SOURCES = src/commands.c src/flags.c src/conversion.c src/output.c main.c
TARGET = test.out

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean