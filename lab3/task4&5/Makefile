CC = gcc
CFLAGS = -g -std=c99 -Wall -Wextra
TARGET = mail_system

SOURCES = main.c \
          src/heap.c \
          src/mail_system.c \
          src/interface.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET) mappings.txt mail.log

.PHONY: all clean run