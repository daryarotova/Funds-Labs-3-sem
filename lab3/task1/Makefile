CC = gcc
CFLAGS = -g -std=c99
SRC = main.c src/convert.c
OBJ = $(SRC:.c=.o)
TARGET = main.out

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
