CC = gcc
CFLAGS = -g -std=c99 -Wall -Wextra -Iinclude
TARGET = liver_manager

SOURCES = main.c \
          src/liver.c \
          src/linked_list.c \
          src/file_operations.c \
          src/search.c \
          src/undo.c \
          src/application.c \
          src/user_interface.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run