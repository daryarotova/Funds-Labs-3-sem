CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -pedantic
TARGET = interpreter

SRC_DIR = src

SOURCES = main.c $(SRC_DIR)/list.c $(SRC_DIR)/utils.c $(SRC_DIR)/parser.c $(SRC_DIR)/runner.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET) trace.log

.PHONY: all clean